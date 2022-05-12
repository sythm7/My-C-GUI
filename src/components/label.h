#ifndef __LABEL_H__
#define __LABEL_H__

/**
 * @file label.h
 * @author sythm
 * @brief Contains all the operations to manipulate a Label component
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "components_utils.h"

/**
 * @brief Label component
 * 
 */
typedef struct Label* Label;

/**
 * @brief Create a Label component
 * 
 * @param font_name 
 * @param font_size 
 * @return Label 
 */
Label init_label(const char* font_name, uint8_t font_size);

/**
 * @brief Get the label surface
 * 
 * @param label 
 * @return SDL_Surface* 
 */
SDL_Surface* get_label_surface(const Label label);

/**
 * @brief Get the label font
 * 
 * @param label 
 * @return TTF_Font* 
 */
TTF_Font* get_label_font(const Label label);

/**
 * @brief Get the label color
 * 
 * @param label 
 * @return Color 
 */
Color get_label_color(const Label label);

/**
 * @brief Get the label text
 * 
 * @param label 
 * @return char* 
 */
char* get_label_text(const Label label);

/**
 * @brief Get the label position
 * 
 * @param label 
 * @return Position 
 */
Position get_label_position(const Label label);

/**
 * @brief Check if the position of a label is absolute on the screen or relative to a layout
 * 
 * @param label 
 * @return true 
 * @return false 
 */
bool is_label_pos_absolute(const Label label);

/**
 * @brief Set the label text
 * 
 * @param label 
 * @param text 
 */
void set_label_text(Label label, char* text);

/**
 * @brief Set the label color
 * 
 * @param label 
 * @param color 
 */
void set_label_color(Label label, Color color);

/**
 * @brief Set the label position
 * 
 * @param label 
 * @param position 
 */
void set_label_position(Label label, Position position);

/**
 * @brief Set the label size
 * 
 * @param label 
 * @param font_size 
 */
void set_label_size(Label label, uint8_t font_size);

#endif