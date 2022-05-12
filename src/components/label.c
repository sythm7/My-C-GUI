#include "label.h"

struct Label {
    RenderingFunction rendering_function;
    DestroyFunction destroy_function;
    ComponentType component_type;
    Panel parent_panel;
    Dimension dimension;
    Position position;
    bool is_visible;
    bool is_rendered;
    bool is_pos_absolute;
    TTF_Font* font;
    Color color;
    char* text;
    char* font_name;
};

SDL_Renderer* get_renderer(Window window);

SDL_Texture* render_ttf(Label label, Window window);

uint8_t render_label(Component component);

char* get_str_copy(const char* source);

void destroy_label(Component component);

Label init_label(const char* font_name, uint8_t font_size) {

    Label label = malloc(sizeof(struct Label));

    if(label == NULL) {
        set_error("init_label() : failed to allocate memory\n");
        return NULL;
    }

    label->component_type = COMPONENT_LABEL;

    label->parent_panel = NULL;

    label->position = init_position(0, 0);

    label->rendering_function = &render_label;

    label->destroy_function = &destroy_label;

    label->is_pos_absolute = false;

    label->font_name = get_str_copy(font_name);

    if(label->font_name == NULL) {
        set_error("init_label() : failed to allocate memory\n");
        destroy_label((Component) label);
        return NULL;
    }

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


uint8_t render_label(Component component) {

    Window window = get_window(component);

    Label label = (Label) component;

    SDL_Texture* texture = render_ttf(label, window);

    if(texture == NULL)
        return set_error("render_label() : failed to render text\n");

    SDL_Rect dimension;

    if(SDL_QueryTexture(texture, NULL, NULL, &dimension.w, &dimension.h) != 0)
        return set_error("render_label() : failed to query label texture\n");
    
    if(is_label_pos_absolute(label)) {
        dimension.x = get_label_position(label).x;
        dimension.y = get_label_position(label).y;
    }
    else {
        // Layout
    }

    if(SDL_RenderCopy(get_renderer(window), texture, NULL, &dimension) != 0)
        return set_error("render_label() : failed to copy the textfield render on the screen\n");

    SDL_DestroyTexture(texture);

    return OPERATION_SUCCESS;
}


SDL_Texture* render_ttf(Label label, Window window) {

    Color color = get_label_color(label);

    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};

    SDL_Surface* surface = TTF_RenderUTF8_Blended(get_label_font(label), get_label_text(label), sdl_color);

    if(surface == NULL)
        return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(get_renderer(window), surface);

    return texture;
}


char* get_str_copy(const char* source) {

    int size = strlen(source);

    char* copy = malloc(size);

    if(copy == NULL)
        return NULL;

    for(int i = 0; i < size; i++) {
        copy[i] = source[i];
    }

    return copy;
}


void destroy_label(Component component) {
    Label label = (Label) component;
    TTF_CloseFont(label->font);
    free(label->font_name);
    free(label);
}