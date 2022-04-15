#include "app_window.h"

struct s_app_window {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

AppWindow init_app_window(const char* title, const Dimension* dimension, const Position* position, const Color* background_color) {

    AppWindow app_window = malloc(sizeof(AppWindow));

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
        exit_app_with_error(NULL, "SDL_Init() error\n");

    app_window->window = SDL_CreateWindow(title, position->x, position->y, dimension->width, dimension->height, SDL_WINDOW_RESIZABLE);

    if(app_window->window == NULL)
        exit_app_with_error(app_window, "SDL_CreateWindow() error\n");

    app_window->renderer = SDL_CreateRenderer(app_window->window, -1, SDL_RENDERER_ACCELERATED);

    if(app_window->renderer == NULL)
        exit_app_with_error(app_window, "SDL_CreateRenderer() error\n");

    fill_app_window(app_window, background_color);

    return app_window;
}


void destroy_app_window(AppWindow app_window) {
    SDL_DestroyRenderer(app_window->renderer);
    SDL_DestroyWindow(app_window->window);
    free(app_window);
}


void render_app_window(AppWindow app_window) {
    SDL_RenderPresent(app_window->renderer);
}


void fill_app_window(AppWindow app_window, const Color* color) {

    if(SDL_SetRenderDrawColor(app_window->renderer, color->r, color->g, color->b, color->a) != 0)
        exit_app_with_error(app_window, "SDL_SetRenderDrawColor() error\n");

    if(SDL_RenderClear(app_window->renderer) != 0)
        exit_app_with_error(app_window, "SDL_RenderClear() error\n");
}


void exit_app_with_error(AppWindow app_window, const char* errMessage) {
    
    destroy_app_window(app_window);
    
    SDL_Log(errMessage, SDL_GetError());

    exit(EXIT_FAILURE);
}