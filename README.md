```html
<span style="color:red">
    <h1><!> WARNING <!></h1>
    <br>
    <p>
        It's still in development. The framework is not complete and is not completely working !
    </p>
</span>
```

# Color Test Document


<style>H1{color:Blue;}</style>
<style>H2{color:DarkOrange;}</style>
<style>p{color:Black;}</style>


## Second Heading

This is a test to see how the colors work.

<h2>Example of project</h2>


The code below will produce the following output once compiled :


![alt text](https://i.imgur.com/ZRcTkEH.png)



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
