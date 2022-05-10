#include "textfield.h"

struct s_textfield {
    Label label;
    Dimension dimension;
    Position position;
    bool is_pos_absolute;
    Color background_color;
};

Textfield init_textfield(char* font_name, uint8_t font_size, Dimension dimension) {

    Label label = init_label(font_name, font_size);

    if(label == NULL)
        return NULL;

    Textfield textfield = malloc(sizeof(struct s_textfield));
    
    textfield->label = label;

    textfield->dimension = dimension;

    return textfield;
}


Label get_textfield_label(Textfield textfield) {
    return textfield->label;
}


Dimension get_textfield_dimension(Textfield textfield) {
    return textfield->dimension;
}


Position get_textfield_position(Textfield textfield) {
    return textfield->position;
}


Color get_textfield_color(Textfield textfield) {
    return textfield->background_color;
}


void set_textfield_color(Textfield textfield, Color background_color) {
    textfield->background_color = background_color;
}


void set_textfield_dimension(Textfield textfield, Dimension dimension) {
    textfield->dimension = dimension;
}


void set_textfield_width(Textfield textfield, uint32_t width) {
    textfield->dimension.width = width;
}


void set_textfield_height(Textfield textfield, uint32_t height) {
    textfield->dimension.height = height;
}


void set_textfield_position(Textfield textfield, Position position) {
    textfield->is_pos_absolute = false;
    textfield->position = position;
}


void set_textfield_position_x(Textfield textfield, uint32_t x) {
    textfield->is_pos_absolute = false;
    textfield->position.x = x;
}


void set_textfield_position_y(Textfield textfield, uint32_t y) {
    textfield->is_pos_absolute = false;
    textfield->position.y = y;
}


void destroy_textfield(Textfield textfield) {
    destroy_label(textfield->label);
    free(textfield);
}