#include "GWindow.h"

#define FILE_DIALOG_EVENT 1
#define FILE_CHOSEN_EVENT 2
#define MAX_WINDOW_TITLE_SIZE 100
#define MAX_WINDOW_NUMBER 3

GWindow window_list[MAX_WINDOW_NUMBER];
int window_list_pos = 0;

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
void window_list_add(GWindow window);
void window_list_del(GWindow window);
int window_focus_event(void* data, SDL_Event* event);
int filter_events(void* data, SDL_Event* event);
GWindow get_gwindow_from_sdl_window(SDL_Window* sdl_window);

int windows_count = 0;
bool waiting_events = false;

int truc = 0;

int id = 0;

int active_window = 0;

#include <stdio.h>

GWindow GWindowInit(const char* title, GColor background_color, SDL_WindowFlags flags) {

    GWindow window = malloc(sizeof(struct GWindow));

    GWindowSetBackgroundColor(window, background_color);

    truc++;
    char truc1[8];
    sprintf(truc1, "App (%d)", truc);

    copy_title(window->title, truc1);

    window->flags = flags;    

    window->dimension = GDimensionInit(0, 0);
    window->position = GPositionInit(0, 0);
    window->panel = NULL;
    window->window = NULL;
    window->renderer = NULL;

    if(windows_count == 0) {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
        return call_window_error(window, "GWindowInit() : failed to init SDL\n");

        if(TTF_Init() != 0)
            return call_window_error(window, "GWindowInit() : failed to init SDL_TTF\n");

        
        if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0)
            return call_window_error(window, "GWindowInit() : failed to init SDL_Image\n");
    }
    
    window->window = SDL_CreateWindow(window->title, window->position.x, window->position.y, window->dimension.width, window->dimension.height, window->flags | SDL_WINDOW_HIDDEN);

    if(window->window == NULL)
        return call_window_error(window, "GWindowInit() : failed to create window\n");

    SDL_SetWindowData(window->window, "ID", &id);

    id++;

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

    if(window->renderer == NULL)
        return call_window_error(window, "GWindowInit() : failed to create renderer\n");

    SDL_AddEventWatch(window_event, window);
    SDL_AddEventWatch(window_focus_event, NULL);

    windows_count++;

    if(window_list_pos == MAX_WINDOW_NUMBER) {
        char number[4];
        char dest[] = "Number of window creation is limited to ";
        sprintf(number, "%d", MAX_WINDOW_NUMBER);
        return call_window_error(window, strcat(dest, number));
    }

    window_list_add(window);

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


int window_focus_event(void* data, SDL_Event* event) {

    if(event->type != SDL_WINDOWEVENT)
        return 0;

    if(event->window.event == SDL_WINDOWEVENT_ENTER || event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        active_window = *((int*) SDL_GetWindowData(SDL_GetWindowFromID(event->window.windowID), "ID"));

    return 0;
}


uint8_t wait_events() {

    waiting_events = true;

    bool is_launched = true;

    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

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
                    SDL_Window* sdl_window = SDL_GetWindowFromID(event.window.windowID);
                    GWindow window = get_gwindow_from_sdl_window(sdl_window);
                    GWindowDestroy(window);
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


void window_list_add(GWindow window) {
    for(int i = 0; i < window_list_pos; i++) {
        //("Adress : %p, Title : %s", (void*)window_list[i], window_list[i]->title);

        if(window_list[i] == NULL) {
            window_list[i] = window;
            SDL_Log("NULL window");
            return;
        }
    }

    window_list[window_list_pos] = window;
    window_list_pos++;
}


GWindow get_gwindow_from_sdl_window(SDL_Window* sdl_window) {

    for(int i = 0; i < window_list_pos; i++) {
        if(window_list[i]->window == sdl_window)
            return window_list[i];
    }

    return NULL;
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

    SDL_DelEventWatch(window_event, window);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);

    if(window->panel != NULL)
        GComponentDestroy((GComponent) window->panel);

    SDL_Log("%s destroyed", window->title);

    for(int i = 0; i < window_list_pos; i++) {
        if(window_list[i] == window) {
            if(i == 1)
                SDL_Log("fenetre trouvee");
            window_list[i] = NULL;
        }
    }

    free(window);

    if(windows_count == 0) {
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
    }
}