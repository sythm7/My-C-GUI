#include "GWindow.h"

#define FILE_DIALOG_EVENT 1
#define FILE_CHOSEN_EVENT 2
#define MAX_WINDOW_TITLE_SIZE 100


struct GWindow {
    SDL_Window* window;
    SDL_Renderer* renderer;
    GDimension dimension;
    GPosition position;
    GColor color;
    GPanel panel;
    SDL_WindowFlags flags;
    char title[MAX_WINDOW_TITLE_SIZE];
};

int window_event(void* data, SDL_Event* event);
uint8_t display_background(GWindow window);
void GPanelSetParentWindow(GPanel panel, GWindow window);
uint8_t render_window(GWindow window);
void* call_window_error(GWindow window, const char* message);
void copy_title(char* destination, const char* source);
void GComponentSetTextureDimension(void* component, SDL_Rect dimension);

int windows_count = 0;
bool waiting_events = false;


GWindow GWindowInit(const char* title, GColor background_color, SDL_WindowFlags flags) {

    GWindow window = malloc(sizeof(struct GWindow));

    GWindowSetBackgroundColor(window, background_color);

    copy_title(window->title, title);

    window->flags = flags;    

    window->dimension = GDimensionInit(0, 0);
    window->position = GPositionInit(0, 0);
    window->panel = NULL;
    window->window = NULL;
    window->renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
        return call_window_error(window, "GWindowInit() : failed to init SDL\n");

    if(TTF_Init() != 0)
        return call_window_error(window, "GWindowInit() : failed to init SDL_TTF\n");

    window->window = SDL_CreateWindow(window->title, window->position.x, window->position.y, window->dimension.width, window->dimension.height, window->flags | SDL_WINDOW_HIDDEN);

    if(window->window == NULL)
        return call_window_error(window, "GWindowInit() : failed to create window\n");

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

    if(window->renderer == NULL)
        return call_window_error(window, "GWindowInit() : failed to create renderer\n");

    SDL_AddEventWatch(window_event, window);

    windows_count++;

    return window;
}


void* call_window_error(GWindow window, const char* message) {

    GError(message);
    GWindowDestroy(window);
    return NULL;
}


uint8_t render_window(GWindow window) {

    if(display_background(window) == G_OPERATION_ERROR)
        return G_OPERATION_ERROR;

    if(window->panel == NULL)
        return G_OPERATION_SUCCESS;

    GRenderingFunction render_panel = GComponentGetRenderingFunction(window->panel);

    GPosition position = GComponentGetPosition(window->panel);

    GDimension dimension = GComponentGetDimension(window->panel);
    
    SDL_Rect texture_rect = {position.x, position.y, dimension.width, dimension.height};

    GComponentSetTextureDimension(window->panel, texture_rect);

    render_panel(window->panel);

    SDL_RenderPresent(window->renderer);

    return G_OPERATION_SUCCESS;
}


void GWindowSetDimension(GWindow window, GDimension dimension) {
    SDL_SetWindowSize(window->window, dimension.width, dimension.height);
}


void GWindowCenterPosition(GWindow window) {
    SDL_SetWindowPosition(window->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}


void GWindowCenterPositionFromWindow(GWindow window_to_center, GWindow other_window) {
    SDL_SetWindowPosition(window_to_center->window, other_window->position.x + other_window->dimension.width / 2, other_window->position.y + other_window->dimension.height / 2);
}


void GWindowSetPanel(GWindow window, GPanel panel) {
    window->panel = panel;
    GPanelSetParentWindow(panel, window);
}


bool GWindowFocused(GWindow window) {
    return SDL_GetMouseFocus() == window->window;
}


uint8_t wait_events() {

    waiting_events = true;

    bool is_launched = true;

    while(is_launched) {

        SDL_Event event;

        if(SDL_WaitEvent(&event) != 1)
            return GError(SDL_GetError());

        
        switch(event.type) {
            case SDL_QUIT :
                is_launched = false;
                break;
            case SDL_WINDOWEVENT :
                if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    SDL_Window* window = SDL_GetWindowFromID(event.window.windowID);
                    SDL_HideWindow(window);
                    windows_count--;
                    is_launched = windows_count == 0 ? false : true;
                }
                break;
            default :
                break;
        }
    }

    waiting_events = false;

    return G_OPERATION_SUCCESS;
}


uint8_t GWindowDisplay(GWindow window) {

    if(render_window(window) == G_OPERATION_ERROR)
        return G_OPERATION_ERROR;

    SDL_ShowWindow(window->window);

    if(! waiting_events)
        return wait_events();

    return G_OPERATION_SUCCESS;
}


uint8_t display_background(GWindow window) {
    if(SDL_SetRenderDrawColor(window->renderer, window->color.r, window->color.g, window->color.b, window->color.a) != 0)
        return GError(SDL_GetError());

    if(SDL_RenderClear(window->renderer) != 0)
        return GError(SDL_GetError());

    if(SDL_SetRenderTarget(window->renderer, NULL) != 0)
        return GError(SDL_GetError());

    return G_OPERATION_SUCCESS;
}


void copy_title(char* destination, const char* source) {
    int i = 0;
    for(; i < strlen(source) && i < MAX_WINDOW_TITLE_SIZE - 1; i++)
        destination[i] = source[i];
    destination[i] = '\0';
}


void GWindowSetBackgroundColor(GWindow window, GColor color) {
    window->color = color;
}


GDimension GWindowGetDimension(GWindow window) {
    return window->dimension;
}


GPosition GWindowGetPosition(GWindow window) {
    return window->position;
}


int window_event(void* data, SDL_Event* event) {
        

    if(event->type == SDL_WINDOWEVENT && (event->window.event == SDL_WINDOWEVENT_RESIZED || event->window.event == SDL_WINDOWEVENT_EXPOSED)) {
        GWindow window = (GWindow) data;
        SDL_Window* sdl_window = SDL_GetWindowFromID(event->window.windowID);
        if(sdl_window == window->window) {
            render_window(window);
        }
    }
    return 0;
}


GPanel GWindowGetPanel(GWindow window) {
    return window->panel;
}


SDL_Window* GWindowGetSDL_Window(GWindow window) {
    return window->window;
}


SDL_Renderer* GWindowGetSDL_Renderer(GWindow window) {
    return window->renderer;
}


void GEventAddListener(GEventFunction event_function, void* data) {
    SDL_AddEventWatch(event_function, data);
}


uint8_t GWindowClose(GWindow window) {

    SDL_Event event;

    event.type = SDL_WINDOWEVENT;
    event.window.event = SDL_WINDOWEVENT_CLOSE;
    event.window.windowID = SDL_GetWindowID(window->window);
    event.window.timestamp = SDL_GetTicks();

    if(SDL_PushEvent(&event) < 0 || event.window.windowID == 0)
        return GError(SDL_GetError());
    
    return G_OPERATION_SUCCESS;
}


void GWindowDestroy(GWindow window) {

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    GComponentDestroy((GComponent) window->panel);
    free(window);
    SDL_Quit();
}