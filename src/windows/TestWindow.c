#include "TestWindow.h"
#include <stdio.h>

GWindow create_test_window() {

    GDimension dimension = GDimensionInit(DEFAULT_LOGIN_WIDTH, DEFAULT_LOGIN_HEIGHT);

    GColor background_color = GColorInit(33, 37, 43, 255);
    
    GWindow window = GWindowInit(DEFAULT_TITLE, background_color, SDL_WINDOW_OPENGL);

    GWindowSetDimension(window, dimension);

    GWindowCenterPosition(window);

    return window;
}