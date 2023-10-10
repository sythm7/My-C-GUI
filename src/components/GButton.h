#ifndef __GBUTTON_H__
#define __GBUTTON_H__

/**
 * @file GButton.h
 * @author sythm
 * @brief Contains all the operations to manipulate a GButton component
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils/GComponentUtils.h"

typedef struct GButton* GButton;
typedef struct GLabel* GLabel;
typedef struct GImage* GImage;

/**
 * @brief Create a Button that you can use in combination with events to make users interact with your app.
 * 
 * @return GButton 
 */
GButton GButtonInit();

/**
 * @brief Set the color which will be displayed as a background of a button.
 * 
 * @param button 
 * @param color 
 */
void GButtonSetColor(GButton button, GColor color);

/**
 * @brief Set the text which will be displayed on a button.
 * 
 * @param button 
 * @param font_name 
 * @param font_size 
 * @param text 
 * @return uint8_t 
 */
uint8_t GButtonSetText(GButton button, const char* font_name, uint8_t font_size, char* text);

#endif