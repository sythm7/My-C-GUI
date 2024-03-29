#ifndef __GLABEL_H__
#define __GLABEL_H__

/**
 * @file label.h
 * @author sythm
 * @brief Contains all the operations to manipulate a GLabel component
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../utils/GComponentUtils.h"

/**
 * @brief GLabel component
 * 
 */
typedef struct GLabel* GLabel;

/**
 * @brief Create a GLabel component
 * 
 * @param font_name 
 * @param font_size 
 * @return GLabel 
 */
GLabel GLabelInit(const char* font_name, uint8_t font_size);

/**
 * @brief Get the label font
 * 
 * @param label 
 * @return TTF_Font* 
 */
TTF_Font* GLabelGetFont(const GLabel label);

/**
 * @brief Get the label color
 * 
 * @param label 
 * @return GColor 
 */
GColor GLabelGetColor(const GLabel label);

/**
 * @brief Get the label text
 * 
 * @param label 
 * @return char* 
 */
char* GLabelGetText(const GLabel label);

/**
 * @brief Set the label text
 * 
 * @param label 
 * @param text 
 * @return uint8_t
 */
uint8_t GLabelSetText(GLabel label, char* text);

/**
 * @brief Set the label color
 * 
 * @param label 
 * @param color 
 */
void GLabelSetColor(GLabel label, GColor color);

#endif