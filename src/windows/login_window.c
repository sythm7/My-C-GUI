#include "login_window.h"

AppWindow create_app_window();

Color background_color;

AppWindow display_login_window() {
    
    AppWindow app_window = create_app_window();

    render_app_window(app_window);

    return app_window;
}


AppWindow create_app_window() {

    Dimension dimension;
    dimension.width = DEFAULT_WIDTH;
    dimension.height = DEFAULT_HEIGHT;

    Position position;
    position.x = SDL_WINDOWPOS_CENTERED;
    position.y = SDL_WINDOWPOS_CENTERED;

    background_color.r = 33;
    background_color.g = 37;
    background_color.b = 43;
    background_color.a = 255;

    return init_app_window("MyApp", &dimension, &position, &background_color);
}