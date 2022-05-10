#ifndef __LABEL_H__
#define __LABEL_H__

#include "components_utils.h"

typedef struct s_label* Label;

Label init_label(char* font_name, uint8_t font_size);

SDL_Surface* get_label_surface(const Label label);

TTF_Font* get_label_font(const Label label);

Color get_label_color(const Label label);

char* get_label_text(const Label label);

Position get_label_position(const Label label);

bool is_label_pos_absolute(const Label label);

void set_label_text(Label label, char* text);

void set_label_color(Label label, Color color);

void set_label_position(Label label, Position position);

void set_label_surface(Label label, SDL_Surface* surface);

void set_label_size(Label label, uint8_t font_size);

void destroy_label(Label label);

#endif