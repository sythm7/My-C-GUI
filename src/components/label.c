#include "label.h"

struct s_label {
    TTF_Font* font;
    Color color;
    char* text;
    char* font_name;
    Position position;
    bool is_pos_absolute;
};

Label init_label(char* font_name, uint8_t font_size) {

    Label label = malloc(sizeof(struct s_label));

    label->position = init_position(0, 0);

    label->is_pos_absolute = false;

    label->font_name = font_name;

    label->font = NULL;

    label->font = TTF_OpenFont(font_name, font_size);

    label->text = " ";

    label->color = init_color(255, 255, 255, 255);

    return label;
}

void set_label_text(Label label, char* text) {

    label->text = text;
}

void set_label_size(Label label, uint8_t font_size) {

    TTF_CloseFont(label->font);

    label->font = TTF_OpenFont(label->font_name, font_size);
}

void set_label_color(Label label, Color color) {

    label->color = color;
}

TTF_Font* get_label_font(const Label label) {
    return label->font;
}

Color get_label_color(const Label label) {
    return label->color;
}

char* get_label_text(const Label label) {
    return label->text;
}

bool is_label_pos_absolute(const Label label) {
    return label->is_pos_absolute;
}

Position get_label_position(const Label label) {
    return label->position;
}

void set_label_position(Label label, Position position) {
    label->position.x = position.x;
    label->position.y = position.y;
    label->is_pos_absolute = true;
}

void destroy_label(Label label) {
    TTF_CloseFont(label->font);
    free(label);
}