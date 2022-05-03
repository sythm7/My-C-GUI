#include "label.h"

struct s_label {
    SDL_Surface* surface;
    TTF_Font* font;
    Color color;
    char* text;
    char* font_name;
};

uint8_t render_ttf(Label label);

Label init_label(char* font_name, uint8_t font_size) {

    Label label = malloc(sizeof(struct s_label));

    label->font_name = font_name;

    label->surface = NULL;

    label->font = NULL;

    label->font = TTF_OpenFont(font_name, font_size);

    label->text = " ";

    label->color = init_color(255, 255, 255, 255);

    if(render_ttf(label) == OPERATION_ERROR)
        return NULL;

    return label;
}

void set_label_text(Label label, char* text) {

    label->text = text;

    render_ttf(label);
}

void set_label_size(Label label, uint8_t font_size) {

    TTF_CloseFont(label->font);

    label->font = TTF_OpenFont(label->font_name, font_size);

    render_ttf(label);
}

void set_label_color(Label label, Color color) {

    label->color = color;

    render_ttf(label);
}

uint8_t render_ttf(Label label) {

    SDL_Color sdl_color = {label->color.r, label->color.g, label->color.b, label->color.a};

    label->surface = TTF_RenderText_Blended(label->font, label->text, sdl_color);

    if(label->surface == NULL) {
        destroy_label(label);
        return OPERATION_ERROR;
    }

    return OPERATION_SUCCESS;
}

SDL_Surface* get_label_surface(const Label label) {
    return label->surface;
}

TTF_Font* get_label_font(const Label label) {
    return label->font;
}

void destroy_label(Label label) {

    TTF_CloseFont(label->font);
    SDL_FreeSurface(label->surface);
    free(label);
}