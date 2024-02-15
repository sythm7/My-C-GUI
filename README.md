# ![Imgur](https://imgur.com/qBWAGTZ.png) My-C-GUI guide

# ![#f03c15](https://imgur.com/v2e0Ih8.png) WARNING ![#f03c15](https://imgur.com/v2e0Ih8.png)
Unfortunately, no release has been published at the moment.
It's still in development. The library is not complete and is not completely working !

<br>

Main things to be added :
+ List component rendering
+ Layouts management
+ Other important components as menus, combo boxes, scrollbars, check boxes, radio buttons, etc...
<br><br>

# How to use the library

On Linux / MacOS :
    In order to use the library, you will need to install the SDL2 library, that provides a solution for rendering graphical applications in C.
    <br>
    [SDL2 wiki](https://wiki.libsdl.org/)
    <br><br>

On Windows :
    As the SDL2 DLLs are already included in the project, you can either plug-and-play or decide tu manually update the SDL files to the newest version (It should be okay because newer versions use the same semantics, they just add new fonctionalities)

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

#include "../engine/GWindow.h"
#include "AppWindow.h"

#define DEFAULT_LOGIN_WIDTH 400
#define DEFAULT_LOGIN_HEIGHT 550
#define DEFAULT_TITLE "MyApp"
#define DEFAULT_FONT "../font/OpticalFiberBold.ttf"
#define ARIAL_FONT "../font/Arial.ttf"

GWindow create_login_window();

#endif
```

<br>

+ login_window.c
```c
#include "LoginWindow.h"

GTextfield username_textfield = NULL;
GTextfield password_textfield = NULL;

int button_click_event(void* data, SDL_Event* event) {

    GButton button = (GButton) data;

    GPosition cursor_position;

    SDL_GetMouseState(&cursor_position.x, &cursor_position.y);

    if(GComponentLeftClicked(event, button)) {
        
        // verify_credentials();
        // Example : 
        // char* username = GTextfieldGetText(username_textfield);
        // char* password = GTextfieldGetText(password_textfield);
        // if(! valid(username, password)) {return 0;}

        GWindowClose(GComponentGetWindow(button));

        GWindow app_window = create_app_window();

        GWindowDisplay(app_window);
    }

    return 0;
}


GWindow create_login_window() {

    GDimension dimension = GDimensionInit(DEFAULT_LOGIN_WIDTH, DEFAULT_LOGIN_HEIGHT);

    GColor background_color = GColorInit(33, 37, 43, 255);
    
    GWindow window = GWindowInit(DEFAULT_TITLE, background_color, SDL_WINDOW_OPENGL);

    GPanel panel = GPanelInit();

    // Labels initialisation
    GLabel welcome_label = GLabelInit(DEFAULT_FONT, 40);
    GLabel username_label = GLabelInit(DEFAULT_FONT, 30);
    GLabel password_label = GLabelInit(DEFAULT_FONT, 30);

    // Textfields initialisation
    username_textfield = GTextfieldInit(ARIAL_FONT, 15, GDimensionInit(150, 30));
    password_textfield = GTextfieldInit(ARIAL_FONT, 15, GDimensionInit(150, 30));

    // GButton initialisation
    GButton ok_button = GButtonInit();

    GLabelSetText(welcome_label, "Welcome to MyApp !");

    GComponentSetPosition(welcome_label, GPositionInit(55, 75));

    GLabelSetText(username_label, "Username :");

    GComponentSetPosition(username_label, GPositionInit(135, 190));

    GLabelSetText(password_label, "Password :");

    GComponentSetPosition(password_label, GPositionInit(135, 300));

    GComponentSetPosition(username_textfield, GPositionInit(125, 240));

    GComponentSetPosition(password_textfield, GPositionInit(125, 340));

    GButtonSetText(ok_button, DEFAULT_FONT, 30, "Ok");

    GButtonSetColor(ok_button, GColorInit(47, 53, 61, 255));
    
    GComponentSetPosition(ok_button, GPositionInit(175, 430));

    GComponentSetDimension(panel, dimension);

    GWindowSetPanel(window, panel);

    GPanelAddComponent(panel, welcome_label);

    GPanelAddComponent(panel, username_label);

    GPanelAddComponent(panel, password_label);

    GPanelAddComponent(panel, username_textfield);

    GPanelAddComponent(panel, password_textfield);

    GPanelAddComponent(panel, ok_button);

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
#include "windows/LoginWindow.h"


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

    GWindowDestroy(login_window);

    return EXIT_SUCCESS;
}
```
