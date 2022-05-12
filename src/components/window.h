#ifndef __WINDOW_H__
#define __WINDOW_H__

/**
 * @file window.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a Window.
 * The window is used to render all the components contained in a specified panel.
 * 
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "panel.h"

/**
 * @brief Window component
 * 
 */
typedef struct Window* Window;

/**
 * @brief Create a Window with the given title and background color.
 * A NULL pointer is returned if an error is encountered.
 * @param title 
 * @param background_color 
 * @return Window
 */
Window init_window(const char* title, Color background_color);

/**
 * @brief Set the window dimension.
 * 
 * @param window 
 * @param dimension 
 */
void set_window_dimension(Window window, Dimension dimension);

/**
 * @brief Center the window position relative to the screen.
 * 
 * @param window 
 */
void center_window_position(Window window);

/**
 * @brief Center the window position relative to another window.
 * 
 * @param window_to_center 
 * @param other_window 
 */
void center_window_position_from_window(Window window_to_center, Window other_window);

/**
 * @brief Render the components and show them on the screen.
 * 
 * @param window 
 * @return uint8_t 
 */
uint8_t display_window(Window window);

/**
 * @brief Set the window background color.
 * 
 * @param window 
 * @param color 
 */
void set_window_color(Window window, Color color);

/**
 * @brief Add a list component to a panel.
 * 
 * @param panel 
 * @param list 
 * @return uint8_t 
 */
uint8_t add_list(Panel panel, List list);

/**
 * @brief Add a label component to a panel.
 * 
 * @param panel 
 * @param label 
 * @return uint8_t 
 */
uint8_t add_label(Panel panel, Label label);

/**
 * @brief Add a textfield component to a panel.
 * 
 * @param panel 
 * @param textfield 
 * @return uint8_t 
 */
uint8_t add_textfield(Panel panel, Textfield textfield);

/**
 * @brief Create a texture that can be drawn and rendered with the SDL functions.
 * 
 * @param window 
 * @param dimension 
 * @return SDL_Texture* 
 */
SDL_Texture* create_texture(Window window, Dimension dimension);

/**
 * @brief Get the window dimension.
 * 
 * @param window 
 * @return Dimension 
 */
Dimension get_window_dimension(Window window);

/**
 * @brief Get the window position.
 * 
 * @param window 
 * @return Position 
 */
Position get_window_position(Window window);

/**
 * @brief Attach the main panel to a window.
 * A window can contain only 1 panel.
 * If no panel is specified for a window, no component will be rendered by this window.
 * 
 * @param window
 * @param panel
 */
void set_panel(Window window, Panel panel);

/**
 * @brief Get the renderer of a window.
 * Useful to make custom renders for custom components.
 * 
 * @param window 
 * @return SDL_Renderer* 
 */
SDL_Renderer* get_renderer(Window window);

/**
 * @brief Free the memory used by a window.
 * 
 * @param window 
 */
void destroy_window(Window window);

#endif