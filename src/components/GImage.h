#ifndef __GIMAGE_H__
#define __GIMAGE_H__

/**
 * @file GImage.h
 * @author sythm
 * @brief Contains all the operations to manipulate a GImage component
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils/GComponentUtils.h"

typedef struct GImage* GImage;

/**
 * @brief Create an image component to render any image file of a specified path.
 * 
 * @return GImage 
 */
GImage GImageInit(const char* image_path, bool is_clickable);


#endif