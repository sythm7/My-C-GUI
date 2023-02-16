#ifndef __GBUTTON_H__
#define __GBUTTON_H__

#include "../utils/GComponentUtils.h"

typedef struct GButton* GButton;
typedef struct GLabel* GLabel;
typedef struct GImage* GImage;

GButton GButtonInit();

void GButtonSetImage(GButton button, GImage image);

void GButtonSetColor(GButton button, GColor color);

uint8_t GButtonSetText(GButton button, const char* font_name, uint8_t font_size, char* text);

void GButtonSetSize(GButton button, GDimension dimension);

void GButtonSetPosition(GButton button, GPosition position);

GPosition GButtonGetPosition(GButton button);

GDimension GButtonGetDimension(GButton button);

void GButtonDestroy(void* component);

#endif