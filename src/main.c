#include <stdio.h>
#include <unistd.h>
#include "windows/login_window.h"

int main(int argc, char** argv) {

    Window window = create_window();

    display_window(window);
    
    bool is_launched = true;

    while(is_launched) {

        SDL_Event event;

        if(SDL_WaitEvent(&event) != 1) {
            perror("SDL_WaitEvent error\n");
            exit(1);
        }

        switch(event.type) {
            case SDL_QUIT :
                is_launched = false;
                break;
            case SDL_TEXTINPUT :
                printf("%s", event.text.text);
                break;
            
            default :
                break;
        }
    }

    destroy_window(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}