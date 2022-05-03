#ifndef __LABEL_H__
#define __LABEL_H__

// A ENLEVER
#include <stdio.h>

#include <SDL_ttf.h>
#include "components_utils.h"

#define FONT_YOGURT_MANGO "font/Yogurt_Mango.ttf"

typedef struct s_label* Label;

// Returns a label or NULL if error
Label init_label(char* font_name, uint8_t font_size);

SDL_Surface* get_label_surface(const Label label);

TTF_Font* get_label_font(const Label label);

void set_label_text(Label label, char* text);

void set_label_color(Label label, Color color);

void destroy_label(Label label);

#endif