#include "GTextfield.h"

#define MAX_TEXT_SIZE 256
#define IS_UTF8_START(c) ((c & 0x80) == 0x00 || (c & 0xE0) == 0xC0 || (c & 0xF0) == 0xE0 || (c & 0xF8) == 0xF0)
#define IS_UTF8_FOLLOWING(c) ((c & 0xC0) == 0x80)

struct GTextfield {
    // Start GComponent
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
    SDL_Rect src_dimension;
    GEventFunction* event_list;
    int event_list_size;
    int event_list_allocated;
    // End GComponent
    
    char text[MAX_TEXT_SIZE];
    char* font_name;
    uint32_t font_size;
    TTF_Font* font;
    bool is_focused;
    GColor background_color;
    GColor font_color;
};


uint8_t GTextfieldRender(void* component);
void GTextfieldDestroy(void* component);
int GTextfieldMouseClickEvent(void* data, SDL_Event* event);
int GTextfieldKeyboardEvent(void* data, SDL_Event* event);
bool GTextfieldConcatenateText(char* destination, const char* source);
void GTextfieldRemoveLastChar(char* destination);
char* get_str_copy(const char* source);
uint8_t GWindowDisplay(GWindow window);
SDL_Renderer* GWindowGetSDL_Renderer(GWindow window);
GPanel GWindowGetPanel(GWindow window);
GComponent* GPanelGetComponentList(const GPanel panel);
uint32_t GPanelGetComponentListSize(const GPanel panel);


GTextfield GTextfieldInit(const char* font_name, uint8_t font_size, GDimension dimension) {

    // GTextfield textfield = malloc(sizeof(struct GTextfield));
    
    // if(textfield == NULL) {
    //     GError("GTextfieldInit() : failed to allocate memory\n");
    //     return NULL;
    // }

    // textfield->rendering_function = &GTextfieldRender;
    // textfield->destroy_function = &GTextfieldDestroy;
    // textfield->component_type = COMPONENT_TEXTFIELD;
    // textfield->position = GPositionInit(0, 0);
    // textfield->is_pos_absolute = false;
    // textfield->dimension = dimension;

    GComponent component = GComponentInit(&GTextfieldRender, &GTextfieldDestroy, COMPONENT_TEXTFIELD);

    if(component == NULL)
        return NULL;

    GTextfield textfield = realloc(component, sizeof(struct GTextfield));

    if(textfield == NULL) {
        GError("GTextfieldInit() : failed to allocate memory\n");
        return NULL;
    }

    textfield->dimension = dimension;
    textfield->text[0] = '\0';
    textfield->font = NULL;
    textfield->font_color = GColorInit(0, 0, 0, 255);
    textfield->font_size = font_size;
    textfield->font_name = get_str_copy(font_name);
    textfield->background_color = GColorInit(255, 255, 255, 255);
    textfield->is_focused = false;
    textfield->font = TTF_OpenFont(textfield->font_name, textfield->font_size);

    if(textfield->font == NULL) {
        char message[] = "GTextfieldInit() : wrong font name '";
        strcat(message, textfield->font_name);
        strcat(message, "'\n");
        GError(message);
        GTextfieldDestroy((GComponent) textfield);
        return NULL;
    }

    GComponentAddListener(&GTextfieldMouseClickEvent, textfield);
    GComponentAddListener(&GTextfieldKeyboardEvent, textfield);

    return textfield;
}


char* GTextfieldGetText(GTextfield textfield) {
    return textfield->text;
}


GColor GTextfieldGetBackgroundColor(GTextfield textfield) {
    return textfield->background_color;
}


void GTextfieldSetBackgroundColor(GTextfield textfield, GColor background_color) {
    textfield->background_color = background_color;
}


void GTextfieldSetFontColor(GTextfield textfield, GColor font_color) {
    textfield->font_color = font_color;
}


uint8_t GTextfieldRender(void* component) {

    GWindow window = GComponentGetWindow(component);

    GTextfield textfield = (GTextfield) component;

    GDimension dimension = textfield->dimension;

    GPosition position = textfield->position;

    SDL_Texture* texture = SDL_CreateTexture(GWindowGetSDL_Renderer(window), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimension.width, dimension.height);

    if(texture == NULL)
        return GError("GTextfieldRender() : failed to create the textfield texture\n");

    if(SDL_SetRenderTarget(GWindowGetSDL_Renderer(window), texture) != 0)
        return GError("GTextfieldRender() : failed to set the textfield texture as a render target\n");

    SDL_Rect outline_rect = {position.x, position.y, dimension.width, dimension.height};

    SDL_Rect interior_rect = {2, 2, dimension.width - 4, dimension.height - 4};

    GColor background_color = textfield->background_color;

    if(SDL_SetRenderDrawColor(GWindowGetSDL_Renderer(window), background_color.r, background_color.g, background_color.b, background_color.a) != 0)
        return GError("GTextfieldRender() : failed to set render draw color\n");

    if(SDL_RenderFillRect(GWindowGetSDL_Renderer(window), &interior_rect) != 0)
        return GError("GTextfieldRender() : failed to fill the rectangle\n");

    if(SDL_SetRenderTarget(GWindowGetSDL_Renderer(window), NULL) != 0)
        return GError("GTextfieldRender() : failed to reset the render target\n");

    if(SDL_RenderCopy(GWindowGetSDL_Renderer(window), texture, NULL, &outline_rect) != 0)
        return GError("GTextfieldRender() : failed to copy the textfield render on the screen\n");

    SDL_DestroyTexture(texture);

    if(strlen(textfield->text) == 0)
        return G_OPERATION_SUCCESS;

    SDL_Rect font_rect = {outline_rect.x + 7, outline_rect.y, outline_rect.w - 14, outline_rect.h};

    SDL_Color font_color = {textfield->font_color.r, textfield->font_color.g, textfield->font_color.b, textfield->font_color.a};

    SDL_Surface* surface = TTF_RenderUTF8_Blended(textfield->font, textfield->text, font_color);

    if(surface == NULL)
        return GError("GTextfieldRender() : failed to render text\n");

    SDL_Texture* font_texture = SDL_CreateTextureFromSurface(GWindowGetSDL_Renderer(window), surface);

    SDL_FreeSurface(surface);

    if(font_texture == NULL)    
        return GError("GTextfieldRender() : failed to create texture from text\n");

    GDimension text_dimension;
    SDL_QueryTexture(font_texture, NULL, NULL, &text_dimension.width, &text_dimension.height);

    int src_x = text_dimension.width >= font_rect.w ? (text_dimension.width - font_rect.w) : 0;
    int src_y = text_dimension.height >= font_rect.h ? (text_dimension.height - font_rect.h) / 2 : 0;

    SDL_Rect src_rect = {src_x, src_y, font_rect.w, font_rect.h};

    int pos_y = text_dimension.height >= font_rect.h ? font_rect.y : font_rect.y + ((font_rect.h - text_dimension.height) / 2);
    int width = text_dimension.width < font_rect.w ? text_dimension.width : font_rect.w;
    int height = text_dimension.height >= font_rect.h ? font_rect.h : text_dimension.height;
    
    SDL_Rect dest_rect = {font_rect.x, pos_y, width, height};

    if(SDL_RenderCopy(GWindowGetSDL_Renderer(window), font_texture, &src_rect, &dest_rect) != 0)
        return GError("GTextfieldRender() : failed to copy the textfield render on the screen\n");

    SDL_DestroyTexture(font_texture);

    return G_OPERATION_SUCCESS;
}


int GTextfieldMouseClickEvent(void* data, SDL_Event* event) {
    
    if(event->type == SDL_MOUSEBUTTONDOWN) {

        GPosition cursor_position;
        SDL_GetMouseState(&cursor_position.x, &cursor_position.y);
        GTextfield textfield = (GTextfield) data;

        GPosition textfield_position = textfield->position;
        GDimension textfield_dimension = textfield->dimension;

        if(cursor_position.x >= textfield_position.x && cursor_position.y >= textfield_position.y 
            && cursor_position.x <= textfield_position.x + textfield_dimension.width && cursor_position.y <= textfield_position.y + textfield_dimension.height) 
        {
            textfield->is_focused = true;
        }
        else {
            textfield->is_focused = false;
        }
    }

    return 0;
}


int GTextfieldKeyboardEvent(void* data, SDL_Event* event) {

    GTextfield textfield = (GTextfield) data;

    if(! textfield->is_focused)
        return 0;

    if(event->type == SDL_TEXTINPUT) {

        if(! GTextfieldConcatenateText(textfield->text, event->text.text))
            return 0;

        if(GWindowDisplay(GComponentGetWindow((GComponent) textfield)) == G_OPERATION_ERROR)
            GError("GTextfieldKeyboardEvent() : can't display render\n");    
    }

    else if(event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {

        GTextfieldRemoveLastChar(textfield->text);

        if(GWindowDisplay(GComponentGetWindow((GComponent) textfield)) == G_OPERATION_ERROR)
            GError("GTextfieldKeyboardEvent() : can't display render\n");
    }

    return 0;
}


bool GTextfieldConcatenateText(char* destination, const char* source) {

    size_t dest_size = strlen(destination);

    if(dest_size >= MAX_TEXT_SIZE)
        return false;

    size_t src_size = strlen(source);

    size_t i = dest_size;

    for(; i < dest_size + src_size; i++) {
        destination[i] = source[i - dest_size];
    }

    destination[i] = '\0';

    return true;
}


void GTextfieldRemoveLastChar(char* destination) {
    
    size_t dest_size = strlen(destination);

    if(dest_size == 0)
        return;

    while(IS_UTF8_FOLLOWING(destination[dest_size - 1])) {
        memmove(destination + (dest_size - 1), destination + dest_size, 1);

        dest_size --;
        if(dest_size == 0)
            return;
    }

    memmove(destination + (dest_size - 1), destination + dest_size, 1);
}


void GTextfieldDestroy(void* component) {

    GTextfield textfield = (GTextfield) component;

    if(textfield->font != NULL)
        TTF_CloseFont(textfield->font);

    free(textfield);
}