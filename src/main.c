#include "windows/login_window.h"

void exit_app_with_error(AppWindow app_window, const char* errMessage);

int main(int argc, char** argv) {

    AppWindow app_window = display_login_window();
    
    bool is_launched = true;

    while(is_launched) {

        SDL_Event event;

        if(SDL_WaitEvent(&event) != 1)
            exit_app_with_error(app_window, "SDL_WaitEvent() error");

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

    destroy_app_window(app_window);

    SDL_Quit();

    return EXIT_SUCCESS;
}