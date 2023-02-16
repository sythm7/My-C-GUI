# [Imgur](https://i.imgur.com/GscqQP0.png) My-C-GUI guide

# ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) WARNING ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)
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

int button_click_event(void* data, SDL_Event* event) {

    Button button = (Button) data;

    Position cursor_position;

    SDL_GetMouseState(&cursor_position.x, &cursor_position.y);

    if(GComponentLeftClicked(event, (Component) button)) {
        GWindowClose(GComponentGetWindow((Component) button));
    }

    return 0;
}


Window create_login_window() {

    Dimension dimension = init_dimension(DEFAULT_LOGIN_WIDTH, DEFAULT_LOGIN_HEIGHT);

    //Color background_color = GColorInit(33, 37, 43, 255);
    Color background_color = GColorInit(33, 37, 43, 0);
    
    Window window = GWindowInit(DEFAULT_TITLE, background_color, SDL_WINDOW_OPENGL);

    Panel panel = GPanelInit();

    // Labels initialisation
    Label welcome_label = GLabelInit(DEFAULT_FONT, 40);
    Label username_label = GLabelInit(DEFAULT_FONT, 30);
    Label password_label = GLabelInit(DEFAULT_FONT, 30);

    // Textfields initialisation
    Textfield username_textfield = GTextfieldInit(DEFAULT_FONT, 15, init_dimension(150, 30));
    Textfield password_textfield = GTextfieldInit(DEFAULT_FONT, 15, init_dimension(150, 30));

    // Button initialisation
    Button ok_button = GButtonInit();

    GLabelSetText(welcome_label, "Welcome to MyApp !");

    GLabelSetPosition(welcome_label, GPositionInit(55, 75));

    GLabelSetText(username_label, "Username :");

    GLabelSetPosition(username_label, GPositionInit(135, 190));

    GLabelSetText(password_label, "Password :");

    GLabelSetPosition(password_label, GPositionInit(135, 300));

    GTextfieldSetPosition(username_textfield, GPositionInit(125, 240));

    GTextfieldSetPosition(password_textfield, GPositionInit(125, 340));

    GButtonSetText(ok_button, DEFAULT_FONT, 30, "Ok");

    GButtonSetColor(ok_button, GColorInit(47, 53, 61, 255));
    
    GButtonSetPosition(ok_button, GPositionInit(175, 430));

    GPanelSetDimension(panel, dimension);

    GWindowSetPanel(window, panel);

    GPanelAddComponent(panel, (Component) welcome_label);

    GPanelAddComponent(panel, (Component) username_label);

    GPanelAddComponent(panel, (Component) password_label);

    GPanelAddComponent(panel, (Component) username_textfield);

    GPanelAddComponent(panel, (Component) password_textfield);

    GPanelAddComponent(panel, (Component) ok_button);

    GWindowSetDimension(window, dimension);

    GWindowCenterPosition(window);

    GEventAddListener(&button_click_event, ok_button);

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

    Window window = create_login_window();

    if(GWindowDisplay(window) == G_OPERATION_ERROR) {
        GWindowDestroy(window);
        return EXIT_FAILURE;
    }

    if(wait_events() == G_OPERATION_ERROR) {
        GWindowDestroy(window);
        return EXIT_FAILURE;
    }
    
    GWindowDestroy(window);

    return EXIT_SUCCESS;
}
```
