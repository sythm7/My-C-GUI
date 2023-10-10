#ifndef __GTEXTFIELD_H__
#define __GTEXTFIELD_H__

/**
 * @file GTextfield.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a GTextfield component.
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "GLabel.h"
#include "stdint.h"

/**
 * @brief GTextfield component. \n
 * You need it if you want to implement a graphical solution to write text informations (like credentials) with the keyboard.
 * 
 */
typedef struct GTextfield* GTextfield;

/**
 * @brief Create a GTextfield component \n
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param font_name 
 * @param font_size 
 * @param dimension 
 * @return GTextfield 
 */
GTextfield GTextfieldInit(const char* font_name, uint8_t font_size, GDimension dimension);

/**
 * @brief Get the written text on a GTextfield.
 * 
 * @param textfield 
 * @return GTextfield 
 */
char* GTextfieldGetText(GTextfield textfield);

/**
 * @brief Get the GTextfield color
 * 
 * @param textfield 
 * @return GColor 
 */
GColor GTextfieldGetBackgroundColor(GTextfield textfield);

/**
 * @brief Set the GTextfield background color
 * 
 * @param textfield 
 * @param background_color 
 */
void GTextfieldSetBackgroundColor(GTextfield textfield, GColor background_color);

/**
 * @brief Set the GTextfield font color
 * 
 * @param textfield 
 * @param font_color 
 */
void GTextfieldSetFontColor(GTextfield textfield, GColor font_color);

#endif