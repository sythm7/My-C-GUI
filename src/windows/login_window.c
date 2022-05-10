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

    Textfield username_textfield = init_textfield("font/OpticalFiberBold.ttf", 30, init_dimension(100, 35));

    Panel panel = init_panel();

    if(panel == NULL)
        exit_app_with_error(window, "login_window -> create_window() error\n");

    set_panel_dimension(panel, dimension);

    set_panel(window, panel);

    add_label(panel, welcome_label);

    add_label(panel, username_label);

    add_label(panel, password_label);

    uint8_t operation = add_textfield(panel, username_textfield);

    if(operation == OPERATION_ERROR) {
        printf("Erreur\n");
        exit(1);
    }

    set_window_dimension(window, dimension);

    center_window_position(window);

    return window;
}