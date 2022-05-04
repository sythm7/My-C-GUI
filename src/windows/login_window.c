#include "login_window.h"

#include <stdio.h>

Window create_window() {

    Dimension dimension = init_dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    Color background_color = init_color(33, 37, 43, 255);
    
    Window window = init_window(DEFAULT_TITLE, background_color);

    Label label = init_label("font/arial.ttf", 35);

    set_label_text(label, "Salut à tous, très chelou les accents");

    Panel panel = init_panel();

    set_panel(window, panel);

    add_label(panel, label);

    set_window_dimension(window, dimension);

    center_window_position(window);

    return window;
}