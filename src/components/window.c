#include "window.h"
#include <stdio.h>

struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Dimension dimension;
    Position position;
    Color color;
    Panel panel;
};

int resizing_event_watcher(void* data, SDL_Event* event);

int text_input_event_watcher(void* data, SDL_Event* event);

void add_component_to_window(Window window, Component component, Panel container_panel);

void display_background(Window window);

void set_parent_window(Panel panel, Window window);

Window init_window(const char* title, Color background_color) {

    Window window = malloc(sizeof(struct Window));

    window->dimension = init_dimension(0, 0);
    window->position = init_position(0, 0);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        set_error("init_window() : failed to init SDL\n");
        return NULL;
    }

    if(TTF_Init() != 0) {
        set_error("init_window() : failed to init SDL_TTF\n");
        return NULL;
    }

    window->window = SDL_CreateWindow(title, window->position.x, window->position.y, window->dimension.width, window->dimension.height, SDL_WINDOW_RESIZABLE);

    if(window->window == NULL) {
        set_error("init_window() : failed to create window\n");
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

    if(window->renderer == NULL) {
        set_error("init_window() : failed to create renderer\n");
        return NULL;
    }

    set_window_color(window, background_color);

    window->panel = NULL;

    SDL_AddEventWatch(resizing_event_watcher, window);
    SDL_StopTextInput();

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
    set_parent_window(panel, window);
}

uint8_t display_window(Window window) {

    display_background(window);

    if(window->panel == NULL)
        return OPERATION_SUCCESS;

    Component* panel_components = get_components(window->panel);
    uint32_t panel_components_size = get_components_size(window->panel);

    for(int i = 0; i < panel_components_size; i++) {
        Component component = panel_components[i];

        RenderingFunction function = get_rendering_function(component);
        if(function != NULL)
            function(component);
        else
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "NULL rendering function for one of the components\n");
    }

    SDL_RenderPresent(window->renderer);

    return OPERATION_SUCCESS;
}

void display_background(Window window) {
    if(SDL_SetRenderDrawColor(window->renderer, window->color.r, window->color.g, window->color.b, window->color.a) != 0)
        set_error("display_background() : failed to set render draw color\n");

    if(SDL_RenderClear(window->renderer) != 0)
        set_error("display_background() : failed to clear render\n");
}

void set_window_color(Window window, Color color) {
    window->color = color;
}

// uint8_t add_textfield(Panel panel, Textfield textfield) {

//     uint8_t operation = add_component(panel, init_component(textfield, COMPONENT_TEXT_FIELD, &render_textfield));

//     if(operation == OPERATION_SUCCESS)
//         SDL_AddEventWatch(text_input_event_watcher, textfield);

//     return operation;
// }


Dimension get_window_dimension(Window window) {
    return window->dimension;
}


Position get_window_position(Window window) {
    return window->position;
}


int resizing_event_watcher(void* data, SDL_Event* event) {

    if(event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        Window window = (Window) data;
        SDL_Window* sdl_window = SDL_GetWindowFromID(event->window.windowID);
        if(sdl_window == window->window) {
            display_window(window);
        }
    }
    return 0;
}


SDL_Renderer* get_renderer(Window window) {
    return window->renderer;
}


void destroy_window(Window window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    destroy_component((Component) window->panel);
    free(window);
}