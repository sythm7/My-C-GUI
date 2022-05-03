#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "panel.h"

typedef struct s_window* Window;

Window init_window(const char* title, Color background_color);

void set_window_dimension(Window window, Dimension dimension);

void center_window_position(Window window);

void center_window_position_from_window(Window window_to_center, Window other_window);

void destroy_window(Window window);

void display_window(Window window);

void exit_app_with_error(Window window, const char* errMessage);

void set_color(Window window, Color color);

SDL_Texture* create_texture(Window window, Dimension dimension);

Dimension get_app_dimension(Window window);

Position get_window_position(Window window);

void set_panel(Window window, Panel panel);

SDL_Renderer* get_renderer(Window window);

#endif