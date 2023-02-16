#include "GLabel.h"

#define DEFAULT_TEXT_SIZE 1 * sizeof(char)

struct GLabel {
    GRenderingFunction rendering_function;
    GDestroyFunction destroy_function;
    GComponentType component_type;
    GPanel parent_panel;
    GDimension dimension;
    GPosition position;
    bool is_component_visible;
    bool is_component_rendered;
    bool is_pos_absolute;
    SDL_Texture* texture;
    SDL_Rect texture_dimension;
    TTF_Font* font;
    GColor color;
    char* text;
    char* font_name;
    uint8_t font_size;
};

SDL_Renderer* GWindowGetSDL_Renderer(GWindow window);
SDL_Texture* GLabelRenderTTF(GLabel label, GWindow window);
uint8_t GLabelRender(void* component);
char* get_str_copy(const char* source);
void GLabelDestroy(void* component);
void GLabelSetFont(GLabel label, TTF_Font* font);
char* GLabelGetFontName(const GLabel label);
uint8_t GLabelGetFontSize(const GLabel label);


GLabel GLabelInit(const char* font_name, uint8_t font_size) {

    GLabel label = malloc(sizeof(struct GLabel));

    if(label == NULL) {
        GError("GLabelInit() : failed to allocate memory\n");
        return NULL;
    }

    label->component_type = COMPONENT_LABEL;

    label->parent_panel = NULL;

    label->position = GPositionInit(0, 0);

    label->dimension = GDimensionInit(0, 0);

    label->rendering_function = &GLabelRender;

    label->destroy_function = &GLabelDestroy;

    label->is_pos_absolute = false;

    label->font_size = font_size;

    label->font_name = get_str_copy(font_name);

    label->text = malloc(DEFAULT_TEXT_SIZE);

    if(label->font_name == NULL || label->text == NULL) {
        GError("GLabelInit() : failed to allocate memory\n");
        GLabelDestroy((GComponent) label);
        return NULL;
    }

    label->font = NULL;
    
    label->text[0] = '\0';

    label->color = GColorInit(255, 255, 255, 255);

    label->texture = NULL;

    return label;
}


uint8_t GLabelSetText(GLabel label, char* text) {
    
    char* temp_text = realloc(label->text, strlen(text));

    if(temp_text == NULL)
        return GError("GLabelSetText() : failed to reallocate memory\n");

    label->text = temp_text;

    strcpy(label->text, text);

    return G_OPERATION_SUCCESS;
}


void GLabelSetColor(GLabel label, GColor color) {

    label->color = color;
}


void GLabelSetFont(GLabel label, TTF_Font* font) {
    label->font = font;
}


TTF_Font* GLabelGetFont(const GLabel label) {
    return label->font;
}


GColor GLabelGetColor(const GLabel label) {
    return label->color;
}


char* GLabelGetText(const GLabel label) {
    return label->text;
}


char* GLabelGetFontName(const GLabel label) {
    return label->font_name;
}


uint8_t GLabelGetFontSize(const GLabel label) {
    return label->font_size;
}


uint8_t GLabelRender(void* component) {

    GWindow window = GComponentGetWindow(component);

    GLabel label = (GLabel) component;

    if(label->text[0] == '\0')
        return G_OPERATION_SUCCESS;

    if(label->font == NULL)
        label->font = TTF_OpenFont(label->font_name, label->font_size);

    if(label->font == NULL) {
        char message[] = "GLabelRender() : wrong font name '";
        strcat(message, label->font_name);
        strcat(message, "'\n");
        return GError(message);
    }
    label->texture = GLabelRenderTTF(label, window);

    if(label->texture == NULL) {
        return GError("GLabelRender() : failed to render text\n");
    }

    SDL_Rect dimension;

    if(SDL_QueryTexture(label->texture, NULL, NULL, &dimension.w, &dimension.h) != 0)
        return GError("GLabelRender() : failed to query label texture\n");

    dimension.x = GComponentGetPosition(label).x;
    dimension.y = GComponentGetPosition(label).y;

    SDL_Rect src_rect = {0, 0, label->texture_dimension.w, label->texture_dimension.h};

    if(SDL_RenderCopy(GWindowGetSDL_Renderer(window), label->texture, &src_rect, &label->texture_dimension) != 0)
        return GError("GLabelRender() : failed to copy the label render on the screen\n");

    label->dimension = GDimensionInit(dimension.w, dimension.h);

    SDL_DestroyTexture(label->texture);

    label->texture = NULL;

    return G_OPERATION_SUCCESS;
}


SDL_Texture* GLabelRenderTTF(GLabel label, GWindow window) {

    if(label->texture != NULL) {
        return label->texture;
    }

    if(strlen(label->text) == 0) {
        return NULL;
    }

    if(label->font == NULL)
        return NULL;

    GColor color = GLabelGetColor(label);

    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};

    SDL_Surface* surface = TTF_RenderUTF8_Blended(GLabelGetFont(label), GLabelGetText(label), sdl_color);

    if(surface == NULL)       
        return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(GWindowGetSDL_Renderer(window), surface);

    SDL_FreeSurface(surface);

    return texture;
}


char* get_str_copy(const char* source) {

    int size = strlen(source);

    char* copy = malloc(size + 1);

    if(copy == NULL)
        return NULL;

    for(int i = 0; i < size; i++) {
        copy[i] = source[i];
    }
    copy[size] = '\0';

    return copy;
}


void GLabelDestroy(void* component) {

    if(component == NULL)
        return;

    GLabel label = (GLabel) component;
    TTF_CloseFont(label->font);
    free(label->text);
    free(label->font_name);
    free(label);
}