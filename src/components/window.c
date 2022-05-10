#include "window.h"
#include "components_rendering.h"

struct s_window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Dimension dimension;
    Position position;
    Color color;
    Panel panel;
};

int resizing_event_watcher(void* data, SDL_Event* event);

void add_component_to_window(Window window, Component component, Panel container_panel);

void display_background(Window window);

Window init_window(const char* title, Color background_color) {

    Window window = malloc(sizeof(struct s_window));

    window->dimension = init_dimension(0, 0);
    window->position = init_position(0, 0);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
        exit_app_with_error(NULL, "Window -> init_window() : SDL_Init() error\n");

    if(TTF_Init() != 0)
        exit_app_with_error(NULL, "Window -> TTF_Init() error\n");

    window->window = SDL_CreateWindow(title, window->position.x, window->position.y, window->dimension.width, window->dimension.height, SDL_WINDOW_RESIZABLE);

    if(window->window == NULL)
        exit_app_with_error(window, "Window -> init_window() : SDL_CreateWindow() error\n");

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

    if(window->renderer == NULL)
        exit_app_with_error(window, "Window -> init_window() : SDL_CreateRenderer() error\n");

    set_window_color(window, background_color);

    window->panel = NULL;

    SDL_AddEventWatch(resizing_event_watcher, window);

    return window;
}

void set_window_dimension(Window window, Dimension dimension) {
    SDL_SetWindowSize(window->window, dimension.width, dimension.height);
}

void center_window_position(Window window) {
    SDL_SetWindowPosition(window->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void center_window_position_from_window(Window window_to_center, Window other_window) {
    SDL_SetWindowPosition(window_to_center->window, other_window->position.x + other_window->dimension.width / 2, other_window->position.y + other_window->dimension.height / 2);
}

void set_panel(Window window, Panel panel) {
    window->panel = panel;
}

void display_window(Window window) {

    display_background(window);

    if(window->panel == NULL)
        return;

    Component* panel_components = get_components(window->panel);
    uint32_t panel_components_size = get_components_size(window->panel);

    for(int i = 0; i < panel_components_size; i++) {
        Component component = panel_components[i];
        rendering_function function = get_rendering_function(component);
        if(function != NULL)
            function(window, component);
        else
            SDL_Log("Warning : NULL rendering function\n");
    }

    SDL_RenderPresent(window->renderer);
}

void display_background(Window window) {
    if(SDL_SetRenderDrawColor(window->renderer, window->color.r, window->color.g, window->color.b, window->color.a) != 0)
        exit_app_with_error(window, "Window -> display_background() : SDL_SetRenderDrawColor() error\n");

    if(SDL_RenderClear(window->renderer) != 0)
        exit_app_with_error(window, "Window -> display_background() : SDL_RenderClear() error\n");
}

void set_window_color(Window window, Color color) {
    window->color = color;
}

uint8_t add_list(Panel panel, List list) {
    return add_component(panel, init_component(list, COMPONENT_LIST, &render_list));
}

uint8_t add_label(Panel panel, Label label) {
    return add_component(panel, init_component(label, COMPONENT_LABEL, &render_label));
}

SDL_Texture* create_texture(Window window, const Dimension dimension) {

    SDL_Texture* texture = NULL;

    texture = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimension.width, dimension.height);

    if(texture == NULL)
        exit_app_with_error(window, "Window -> create_texture() : SDL_CreateTexture() error\n");

    return texture;
}


void set_render_target(Window window, SDL_Texture* texture) {

    if(SDL_SetRenderTarget(window->renderer, texture) != 0)
        exit_app_with_error(window, "Window -> set_render_target() : SDL_SetRenderTarget() error\n");
}


void set_renderer_target(Window window) {

    if(SDL_SetRenderTarget(window->renderer, NULL) != 0)
        exit_app_with_error(window, "Window -> set_renderer_target() : SDL_SetRenderTarget() error\n");
}


Dimension get_window_dimension(Window window) {
    return window->dimension;
}

Position get_window_position(Window window) {
    return window->position;
}


int resizing_event_watcher(void* data, SDL_Event* event) {

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        Window window = (Window) data;
        SDL_Window* sdl_window = SDL_GetWindowFromID(event->window.windowID);
        if (sdl_window == window->window) {
            display_window(window);
        }
    }
    return 0;
}

void destroy_window(Window window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}

void exit_app_with_error(Window window, const char* errMessage) {
    
    destroy_window(window);
    
    SDL_Log(errMessage, SDL_GetError());

    exit(EXIT_FAILURE);
}

SDL_Renderer* get_renderer(Window window) {
    return window->renderer;
}