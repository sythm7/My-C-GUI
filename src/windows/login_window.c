#include "login_window.h"
#include <windows.h>
#include <locale.h>

#include <stdio.h>

Window create_window() {

    Dimension dimension = init_dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    Color background_color = init_color(33, 37, 43, 255);

    setlocale(LC_ALL, "");

    Window window = init_window(DEFAULT_TITLE, background_color);

    Label label = init_label("font/arial.ttf", 35);

    set_label_text(label, "Salut comment ça va aujourd'hui t'es tranquille et tout ? Super Nice alors c'est cool de savoir ça");

    Panel panel = init_panel();

    set_panel(window, panel);

    add_label(panel, label);

    set_window_dimension(window, dimension);

    center_window_position(window);

    return window;
}