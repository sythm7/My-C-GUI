#ifndef __TEXTFIELD_H__
#define __TEXTFIELD_H__

#include "label.h"
#include "stdint.h"

typedef struct s_textfield* Textfield;

Textfield init_textfield(char* font_name, uint8_t font_size, Dimension dimension);

Label get_textfield_label(Textfield textfield);

Dimension get_textfield_dimension(Textfield textfield);

Position get_textfield_position(Textfield textfield);

Color get_textfield_color(Textfield textfield);

void set_textfield_color(Textfield textfield, Color background_color);

void set_textfield_dimension(Textfield textfield, Dimension dimension);

void set_textfield_width(Textfield textfield, uint32_t width);

void set_textfield_height(Textfield textfield, uint32_t height);

void set_textfield_position(Textfield textfield, Position position);

void set_textfield_position_x(Textfield textfield, uint32_t x);

void set_textfield_position_y(Textfield textfield, uint32_t y);

void destroy_textfield(Textfield textfield);

#endif