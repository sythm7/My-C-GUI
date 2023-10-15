#include <stdio.h>
#include <unistd.h>
#include "windows/LoginWindow.h"
#include "windows/AppWindow.h"
#include <stdlib.h>
#include <libgen.h>

#define MAX_PATH 256

char G_Program_Path[MAX_PATH];

void init_prog_path();


int main(int argc, char* argv[]) {

    init_prog_path();

    GWindow login_window = create_login_window();

    if(GWindowDisplay(login_window) == G_OPERATION_ERROR) {
        GWindowDestroy(login_window);
        return EXIT_FAILURE;
    }
    
    // -------------
    // Lines of code
    //--------------

    // DEINITIALISER LES COMPOSANTS SDL

    // if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
    //         return GError("GWindowInit() : failed to init SDL\n");

    // SDL_Window* window = SDL_CreateWindow("APP", 600, 300, 800, 600, SDL_WINDOW_RESIZABLE);

    // if(window == NULL)
    //     return GError("GWindowInit() : failed to create window\n");

    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // if(renderer == NULL)
    //     return GError("GWindowInit() : failed to create renderer\n");

    // if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0) != 0)
    //     return GError(SDL_GetError());

    // if(SDL_RenderClear(renderer) != 0)
    //     return GError(SDL_GetError());

    // if(SDL_SetRenderTarget(renderer, NULL) != 0)
    //     return GError(SDL_GetError());

    // bool is_launched = true;

    // SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

    // while(is_launched) {

    //     SDL_Event event;

    //     if(SDL_WaitEvent(&event) != 1)
    //         return GError(SDL_GetError());
            
        
    //     switch(event.type) {
    //         case SDL_QUIT :
    //             is_launched = false;
    //             break;
    //         case SDL_WINDOWEVENT :

    //             if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
    //                 SDL_Window* sdl_window = SDL_GetWindowFromID(event.window.windowID);
    //                 SDL_DestroyWindow(sdl_window);
    //                 is_launched = false;
    //             }
    //             break;
    //         default :
    //             break;
    //     }
    // }


    // // pid_t p = fork();

    // // if(p == 0) {
        
    // // }
    
    return EXIT_SUCCESS;
}



void init_prog_path() {

    #if defined(_WIN32)
    strcpy(G_Program_Path, dirname(_pgmptr));
    #elif defined(__linux__)
    pid_t pid = getpid();

    char path[256];
    char path2[256];
    snprintf(path, sizeof(path), "/proc/%d/exe", pid);
    readlink(path, path2, 256);
    strcpy(G_Program_Path, dirname(path2));
    printf("%s\n", G_Program_Path);
    #endif

    chdir(G_Program_Path);
}