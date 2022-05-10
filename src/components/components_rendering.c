#include "components_rendering.h"

SDL_Texture* render_ttf(Label label, Window window);


void render_textfield(void* data, Component component) {

    Window window = (Window) data;

    Textfield textfield = (Textfield) get_component_content(component);

    Dimension dimension = get_textfield_dimension(textfield);

    Position position = get_textfield_position(textfield);

    SDL_Texture* texture = SDL_CreateTexture(get_renderer(window), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimension.width, dimension.height);

    SDL_SetRenderTarget(get_renderer(window), texture);

    SDL_Rect rect = {position.x, position.y, dimension.width, dimension.height};

    Color background_color = get_textfield_color(textfield);

    SDL_SetRenderDrawColor(get_renderer(window), 0, 0, 0, 255);

    SDL_RenderFillRect(get_renderer(window), &rect);

    SDL_SetRenderDrawColor(get_renderer(window), background_color.r, background_color.g, background_color.b, background_color.a);

    rect.x+= 3;
    rect.y -= 3;
    rect.w -= 6;
    rect.y -= 6;

    SDL_RenderFillRect(get_renderer(window), &rect);

    SDL_SetRenderTarget(get_renderer(window), NULL);
}


void render_label(void* data, Component component) {

    Window window = (Window) data;

    Label label = (Label) get_component_content(component);

    SDL_Texture* texture = render_ttf(label, window);

    if(texture == NULL)
        exit_app_with_error(window, "Window -> add_component_to_window() error\n");

    SDL_Rect dimension;

    SDL_QueryTexture(texture, NULL, NULL, &dimension.w, &dimension.h);
    
    if(is_label_pos_absolute(label)) {
        dimension.x = get_label_position(label).x;
        dimension.y = get_label_position(label).y;
    }
    else {
        // Layout
    }

    SDL_RenderCopy(get_renderer(window), texture, NULL, &dimension);

    SDL_DestroyTexture(texture);
}


void render_list(void* data, Component component) {
    // TODO
}


SDL_Texture* render_ttf(Label label, Window window) {

    Color color = get_label_color(label);

    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};

    SDL_Surface* surface = TTF_RenderUTF8_Blended(get_label_font(label), get_label_text(label), sdl_color);

    if(surface == NULL) {
        destroy_label(label);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(get_renderer(window), surface);

    return texture;
}