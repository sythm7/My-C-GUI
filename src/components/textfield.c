#include "textfield.h"

uint8_t render_textfield(Component component);

void destroy_textfield(Component component);

int text_input_event_watcher(void* data, SDL_Event* event);

SDL_Renderer* get_renderer(Window window);

struct Textfield {
    RenderingFunction rendering_function;
    DestroyFunction destroy_function;
    ComponentType component_type;
    Panel parent_panel;
    Dimension dimension;
    Position position;
    bool is_visible;
    bool is_rendered;
    bool is_pos_absolute;
    Label label;
    bool is_focused;
    Color background_color;
};

Textfield init_textfield(const char* font_name, uint8_t font_size, Dimension dimension) {

    Label label = init_label(font_name, font_size);

    if(label == NULL) {
        set_error("init_textfield() : failed to allocate memory\n");
        return NULL;
    }

    Textfield textfield = malloc(sizeof(struct Textfield));
    
    if(textfield == NULL) {
        set_error("init_textfield() : failed to allocate memory\n");
        return NULL;
    }

    textfield->rendering_function = &render_textfield;

    textfield->destroy_function = &destroy_textfield;

    textfield->component_type = COMPONENT_TEXT_FIELD;

    textfield->label = label;

    textfield->background_color = init_color(255, 255, 255, 255);

    textfield->position = init_position(0, 0);

    set_label_color(textfield->label, init_color(0, 0, 0, 255));

    textfield->is_pos_absolute = false;

    textfield->is_focused = false;

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


void set_textfield_background_color(Textfield textfield, Color background_color) {
    textfield->background_color = background_color;
}


void set_textfield_text_color(Textfield textfield, Color text_color) {
    set_label_color(textfield->label, text_color);
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
    textfield->is_pos_absolute = true;
    textfield->position = position;
}


void set_textfield_position_x(Textfield textfield, uint32_t x) {
    textfield->is_pos_absolute = true;
    textfield->position.x = x;
}


void set_textfield_position_y(Textfield textfield, uint32_t y) {
    textfield->is_pos_absolute = true;
    textfield->position.y = y;
}


uint8_t render_textfield(Component component) {

    Window window = get_window(component);

    Textfield textfield = (Textfield) component;

    Dimension dimension = textfield->dimension;

    Position position = textfield->position;

    SDL_Texture* texture = SDL_CreateTexture(get_renderer(window), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimension.width, dimension.height);

    if(texture == NULL)
        return set_error("render_textfield() : failed to create the textfield texture\n");

    if(SDL_SetRenderTarget(get_renderer(window), texture) != 0)
        return set_error("render_textfield() : failed to set the textfield texture as a render target\n");

    SDL_Rect outline_rect = {position.x, position.y, dimension.width, dimension.height};

    SDL_Rect interior_rect = {2, 2, dimension.width - 4, dimension.height - 4};

    Color background_color = textfield->background_color;

    if(SDL_SetRenderDrawColor(get_renderer(window), background_color.r, background_color.g, background_color.b, background_color.a) != 0)
        return set_error("render_textfield() : failed to set render draw color\n");

    if(SDL_RenderFillRect(get_renderer(window), &interior_rect) != 0)
        return set_error("render_textfield() : failed to fill the rectangle\n");

    if(SDL_SetRenderTarget(get_renderer(window), NULL) != 0)
        return set_error("render_textfield() : failed to reset the render target\n");

    if(SDL_RenderCopy(get_renderer(window), texture, NULL, &outline_rect) != 0)
        return set_error("render_textfield() : failed to copy the textfield render on the screen\n");

    SDL_DestroyTexture(texture);

    SDL_DelEventWatch(&text_input_event_watcher, textfield);
    SDL_AddEventWatch(&text_input_event_watcher, textfield);

    return OPERATION_SUCCESS;
}


int text_input_event_watcher(void* data, SDL_Event* event) {
    
    if(event->type == SDL_MOUSEBUTTONDOWN) {

        Position cursor_position;
        SDL_GetMouseState(&cursor_position.x, &cursor_position.y);
        Textfield textfield = (Textfield) data;

        Position textfield_position = textfield->position;
        Dimension textfield_dimension = textfield->dimension;

        if(cursor_position.x >= textfield_position.x && cursor_position.y >= textfield_position.y 
            && cursor_position.x <= textfield_position.x + textfield_dimension.width && cursor_position.y <= textfield_position.y + textfield_dimension.height) 
        {
            SDL_Rect input_rect = {textfield_position.x, textfield_position.y, textfield_dimension.width, textfield_dimension.height};
            SDL_StartTextInput();
            SDL_SetTextInputRect(&input_rect);
            SDL_Log("Focused textfield\n");
        }

    }

    return 0;
}


void destroy_textfield(Component component) {

    Textfield textfield = (Textfield) component;
    destroy_component((Component) textfield->label);
    free(textfield);
}