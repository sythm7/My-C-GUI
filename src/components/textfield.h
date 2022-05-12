#ifndef __TEXTFIELD_H__
#define __TEXTFIELD_H__

/**
 * @file textfield.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a Textfield component.
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "label.h"
#include "stdint.h"

/**
 * @brief Textfield component
 * 
 */
typedef struct Textfield* Textfield;

/**
 * @brief Create a Textfield component
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param font_name 
 * @param font_size 
 * @param dimension 
 * @return Textfield 
 */
Textfield init_textfield(const char* font_name, uint8_t font_size, Dimension dimension);

/**
 * @brief Get the textfield label
 * 
 * @param textfield 
 * @return Label 
 */
Label get_textfield_label(Textfield textfield);

/**
 * @brief Get the textfield dimension
 * 
 * @param textfield 
 * @return Dimension 
 */
Dimension get_textfield_dimension(Textfield textfield);

/**
 * @brief Get the textfield position
 * 
 * @param textfield 
 * @return Position 
 */
Position get_textfield_position(Textfield textfield);

/**
 * @brief Get the textfield color
 * 
 * @param textfield 
 * @return Color 
 */
Color get_textfield_color(Textfield textfield);

/**
 * @brief Set the textfield background color
 * 
 * @param textfield 
 * @param background_color 
 */
void set_textfield_background_color(Textfield textfield, Color background_color);

/**
 * @brief Set the textfield text color
 * 
 * @param textfield 
 * @param text_color 
 */
void set_textfield_text_color(Textfield textfield, Color text_color);

/**
 * @brief Set the textfield dimension
 * 
 * @param textfield 
 * @param dimension 
 */
void set_textfield_dimension(Textfield textfield, Dimension dimension);

/**
 * @brief Set the textfield width
 * 
 * @param textfield 
 * @param width 
 */
void set_textfield_width(Textfield textfield, uint32_t width);

/**
 * @brief Set the textfield height
 * 
 * @param textfield 
 * @param height 
 */
void set_textfield_height(Textfield textfield, uint32_t height);

/**
 * @brief Set the textfield position
 * 
 * @param textfield 
 * @param position 
 */
void set_textfield_position(Textfield textfield, Position position);

/**
 * @brief Set the textfield position x
 * 
 * @param textfield 
 * @param x 
 */
void set_textfield_position_x(Textfield textfield, uint32_t x);

/**
 * @brief Set the textfield position y
 * 
 * @param textfield 
 * @param y 
 */
void set_textfield_position_y(Textfield textfield, uint32_t y);

#endif