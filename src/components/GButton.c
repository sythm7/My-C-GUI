#include "GButton.h"
#include "GLabel.h"

#define MAX_WIDTH 99999
#define DEFAULT_COLOR GColorInit(140, 140, 140, 255)
#define COLOR_BLACK 140, 140, 140, 255
#define HOVERED_BUTTON_MULTIPLICATOR 1.15f
#define PRESSED_BUTTON_MULTIPLICATOR 1.30f

struct GButton {
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
    
    GLabel label;
    GImage image;
    GColor color;
    bool is_hovered;
    bool is_pressed;
};

void GComponentSetParentPanel(void* component, GPanel panel);
GLabel GLabelInit(const char* font_name, uint8_t font_size);
void GLabelSetColor(GLabel label, GColor color);
uint8_t GLabelSetText(GLabel label, char* text);
TTF_Font* GLabelGetFont(const GLabel label);
char* GLabelGetText(const GLabel label);
void GLabelDestroy(void* component);
SDL_Texture* GLabelRenderTTF(GLabel label, GWindow window);
uint8_t GLabelRender(void* component);
uint8_t GButtonRender(void* component);
int GButtonEvent(void* data, SDL_Event* event);
SDL_Renderer* GWindowGetSDL_Renderer(GWindow window);
void GLabelSetFont(GLabel label, TTF_Font* font);
char* GLabelGetFontName(const GLabel label);
uint8_t GLabelGetFontSize(const GLabel label);
void GComponentAdaptDimension(void* component);
void GButtonDestroy(void* component);


GButton GButtonInit() {

    GComponent component = GComponentInit(&GButtonRender, &GButtonDestroy, COMPONENT_BUTTON);

    if(component == NULL)
        return NULL;

    GButton button = realloc(component, sizeof(struct GButton));

    if(button == NULL) {
        GError("GButtonInit() : failed to allocate memory\n");
        return NULL;
    }

    // button->rendering_function = &GButtonRender;
    // button->destroy_function = &GButtonDestroy;
    // button->component_type = COMPONENT_BUTTON;
    // button->parent_panel = NULL;
    // button->position = GPositionInit(0, 0);
    // button->dimension = GDimensionInit(-1, -1);
    // button->is_component_visible = true;
    // button->is_component_rendered = false;
    // button->is_pos_absolute = false;
    button->label = NULL;
    button->color = DEFAULT_COLOR;
    button->is_hovered = false;
    button->is_pressed = false;
    GComponentAddListener(&GButtonEvent, button);

    return button;
}


void GButtonSetColor(GButton button, GColor color) {
    button->color = color;
}


uint8_t GButtonSetText(GButton button, const char* font_name, uint8_t font_size, char* text) {

    button->label = GLabelInit(font_name, font_size);

    if(button->label == NULL)
        return GError("GButtonSetText() : GButton label is NULL\n");

    GLabelSetText(button->label, text);

    return G_OPERATION_SUCCESS;
}


int GButtonEvent(void* data, SDL_Event* event) {

    bool is_mouse_down = false;
    bool is_mouse_up = false;

    if(GMouseLeftPressed(event))
        is_mouse_down = true;
    else if(GMouseLeftClicked(event))
        is_mouse_up = true;
    else if(event->type != SDL_MOUSEMOTION)
        return 0;

    GButton button = (GButton) data;

    if(GComponentHovered(event, button)) 
    {
        if(! button->is_hovered) {
            button->is_hovered = true;
            GButtonRender(button);
            SDL_RenderPresent(GWindowGetSDL_Renderer(GComponentGetWindow(button)));
        }
        if(is_mouse_down) {
            button->is_hovered = true;
            button->is_pressed = true;
            GButtonRender(button);
            SDL_RenderPresent(GWindowGetSDL_Renderer(GComponentGetWindow(button)));
        }
        if(is_mouse_up) {
            button->is_hovered = true;
            button->is_pressed = false;
            GButtonRender(button);
            SDL_RenderPresent(GWindowGetSDL_Renderer(GComponentGetWindow(button)));
        }
    }
    else {
        if(button->is_hovered) {
            button->is_hovered = false;
            GButtonRender(button);
            SDL_RenderPresent(GWindowGetSDL_Renderer(GComponentGetWindow(button)));
        }
        if(button->is_pressed) {
            button->is_pressed = false;
            GButtonRender(button);
            SDL_RenderPresent(GWindowGetSDL_Renderer(GComponentGetWindow(button)));
        }
    }
    return 0;
}


uint8_t GButtonRender(void* component) {

    GButton button = (GButton) component;
    
    int count = 0;
    int width = 0;
    int height = 0;

    // Render label
    if(GLabelGetFont(button->label) == NULL) {
        TTF_Font* label_font = TTF_OpenFont(GLabelGetFontName(button->label), GLabelGetFontSize(button->label));

        if(label_font == NULL) {
            char message[] = "GButtonRender() : wrong font name '";
            strcat(message, GLabelGetFontName(button->label));
            strcat(message, "'\n");
            return GError(message);
        }

        GLabelSetFont(button->label, label_font);

        TTF_MeasureUTF8(label_font, GLabelGetText(button->label), MAX_WIDTH, &width, &count);

        height = TTF_FontHeight(GLabelGetFont(button->label));
    }

    TTF_MeasureUTF8(GLabelGetFont(button->label), GLabelGetText(button->label), MAX_WIDTH, &width, &count);

    height = TTF_FontHeight(GLabelGetFont(button->label));
  

    GDimension dimension = GDimensionInit(width, height);

    GWindow window = GComponentGetWindow(button);

    GComponentSetParentPanel(button->label, button->parent_panel);

    GComponentSetPosition(button->label, GPositionInit(button->position.x + 10, button->position.y + 10));

    SDL_Rect button_texture_dimension = {0, 0, dimension.width + 20, dimension.height + 20};

    SDL_Rect button_dimension = {button->position.x, button->position.y, button_texture_dimension.w, button_texture_dimension.h};

    SDL_Renderer* renderer = GWindowGetSDL_Renderer(window);

    SDL_Texture* button_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, button_dimension.w, button_dimension.h);

    if(button_texture == NULL)
        return GError("GButtonRender() : failed to create the button texture\n");

    if(SDL_SetRenderTarget(renderer, button_texture) != 0)
        return GError("GButtonRender() : failed to set render target\n");


    GColor render_color = button->is_hovered ? GColorSetLuminance(button->color, HOVERED_BUTTON_MULTIPLICATOR) : button->color;

    render_color = button->is_pressed ? GColorSetLuminance(button->color, PRESSED_BUTTON_MULTIPLICATOR) : render_color;

    if(SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a) != 0)
        return GError("GButtonRender() : failed to set render draw color\n");

    if(SDL_RenderFillRect(renderer, &button_texture_dimension) != 0)
        return GError("GButtonRender() : failed to draw button\n");

    if(SDL_SetRenderDrawColor(renderer, COLOR_BLACK) != 0)
        return GError("GButtonRender() : failed to set render draw color\n");

    if(SDL_RenderDrawRect(renderer, &button_texture_dimension) != 0)
        return GError("GButtonRender() : failed to draw button outline\n");

    if(SDL_SetRenderTarget(renderer, NULL) != 0)
        return GError("GButtonRender() : failed to reset render target\n");

    SDL_Rect src_rect = {0, 0, button->texture_dimension.w, button->texture_dimension.h};

    if(SDL_RenderCopy(renderer, button_texture, &src_rect, &button->texture_dimension) != 0)
        return GError("GButtonRender() : failed to render button\n");

    GComponentAdaptDimension(button->label);

    if(GLabelRender(button->label) != G_OPERATION_SUCCESS)
        return GError("GButtonRender() : failed to render button label\n");

    SDL_DestroyTexture(button_texture);

    button->dimension = GDimensionInit(button_dimension.w, button_dimension.h);

    return G_OPERATION_SUCCESS;
}


void GButtonDestroy(void* component) {

    if(component == NULL)
        return;

    GButton button = (GButton) component;

    GLabelDestroy(button->label);

    free(button);
}