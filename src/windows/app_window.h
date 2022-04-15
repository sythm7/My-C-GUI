#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_WIDTH 960
#define DEFAULT_HEIGHT 560
#define DEFAULT_TITLE "MyApp"

typedef enum{false, true} bool;

typedef struct {
    int width;
    int height;
} Dimension;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

typedef struct s_app_window* AppWindow;

AppWindow init_app_window(const char* title, const Dimension* dimension, const Position* position, const Color* background_color);

void destroy_app_window(AppWindow app_window);

void render_app_window(AppWindow app_window);

void exit_app_with_error(AppWindow app_window, const char* errMessage);

void fill_app_window(AppWindow app_window, const Color* color);

#endif