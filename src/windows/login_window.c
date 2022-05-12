#include "login_window.h"

#include <stdio.h>

Label welcome_label = NULL;
Label username_label = NULL;
Label password_label = NULL;


Window create_window() {

    Dimension dimension = init_dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    Color background_color = init_color(33, 37, 43, 255);
    
    Window window = init_window(DEFAULT_TITLE, background_color);

    Panel panel = init_panel();

    // Labels initialisation
    welcome_label = init_label(DEFAULT_FONT, 50);

    username_label = init_label(DEFAULT_FONT, 30);

    password_label = init_label(DEFAULT_FONT, 30);

    // Textfields initialisation
    Textfield username_textfield = init_textfield(DEFAULT_FONT, 30, init_dimension(150, 30));

    Textfield password_textfield = init_textfield(DEFAULT_FONT, 30, init_dimension(150, 30));

    set_label_text(welcome_label, "Welcome to MyApp !");

    set_label_position(welcome_label, init_position(300, 100));

    set_label_text(username_label, "Username :");

    set_label_position(username_label, init_position(420, 230));

    set_label_text(password_label, "Password :");

    set_label_position(password_label, init_position(420, 340));

    set_textfield_position(username_textfield, init_position(410, 270));

    set_textfield_position(password_textfield, init_position(410, 380));

    set_panel_dimension(panel, dimension);

    set_panel(window, panel);

    add_component(panel, (Component) welcome_label);

    add_component(panel, (Component) username_label);

    add_component(panel, (Component) password_label);

    add_component(panel, (Component) username_textfield);

    add_component(panel, (Component) password_textfield);

    set_window_dimension(window, dimension);

    center_window_position(window);

    return window;
}