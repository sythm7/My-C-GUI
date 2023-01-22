# ![Imgur](https://imgur.com/qBWAGTZ.png) My-C-GUI guide

# ![#f03c15](https://imgur.com/v2e0Ih8.png) WARNING ![#f03c15](https://imgur.com/v2e0Ih8.png)
Unfortunately, no release has been published at the moment.
It's still in development. The framework is not complete and is not completely working !

<br>

Main things to be added :
+ List component rendering
+ Layouts management
+ Other important components as menus, combo boxes, scrollbars, check boxes, radio buttons, etc...
<br><br>

# How to use the framework
In order to use the framework, you will need to install the SDL2 library, that provides a solution for rendering graphical applications in C.
<br>
[SDL2 wiki](https://wiki.libsdl.org/)
<br><br>

# Framework compatibility
This framework was designed to be compatible with Windows and all Linux distributions.
However, it hasn't been tested with MacOS.
<br><br>

# Example of project

The code below will produce the following output once compiled :

![Imgur](https://i.imgur.com/GscqQP0.png)

<br>

+ login_window. h
```h
#ifndef __LOGIN_WINDOW_H__
#define __LOGIN_WINDOW_H__

#include "../components/window.h"

#define DEFAULT_WIDTH 960
#define DEFAULT_HEIGHT 560
#define DEFAULT_TITLE "MyApp"

Window create_window();

#endif
```

<br>

+ login_window.c
```c
#include "login_window.h"

#include <stdio.h>

Window create_window() {

    Dimension dimension = init_dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    Color background_color = init_color(33, 37, 43, 255);
    
    Window window = init_window(DEFAULT_TITLE, background_color);

    Label welcome_label = init_label("font/OpticalFiberBold.ttf", 50);

    set_label_text(welcome_label, "Welcome to MyApp !");

    set_label_position(welcome_label, init_position(300, 100));

    Label username_label = init_label("font/OpticalFiberBold.ttf", 30);

    set_label_text(username_label, "Username :");

    set_label_position(username_label, init_position(420, 230));

    Label password_label = init_label("font/OpticalFiberBold.ttf", 30);

    set_label_text(password_label, "Password :");

    set_label_position(password_label, init_position(420, 340));

    Textfield username_textfield = init_textfield("font/OpticalFiberBold.ttf", 30, init_dimension(150, 30));

    set_textfield_position(username_textfield, init_position(410, 270));

    Panel panel = init_panel();

    if(panel == NULL)
        exit_app_with_error(window, "login_window -> create_window() error\n");

    set_panel_dimension(panel, dimension);

    set_panel(window, panel);

    add_label(panel, welcome_label);

    add_label(panel, username_label);

    add_label(panel, password_label);

    add_textfield(panel, username_textfield);

    set_window_dimension(window, dimension);

    center_window_position(window);

    return window;
}
```

<br>

+ main.c
```c
#include <stdio.h>
#include <unistd.h>
#include "windows/login_window.h"

void exit_app_with_error(Window window, const char* errMessage);

int main(int argc, char** argv) {

    Window window = create_window();  

    display_window(window);
    
    bool is_launched = true;

    while(is_launched) {

        SDL_Event event;

        if(SDL_WaitEvent(&event) != 1)
            exit_app_with_error(window, "SDL_WaitEvent() error");

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
```
