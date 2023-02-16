#include "GComponentUtils.h"

char G_Program_Path[256];

struct GComponent {
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
};

GWindow GPanelGetWindow(const GPanel panel);

GComponent GComponentInit(GRenderingFunction rendering_function) {

    GComponent component = malloc(sizeof(struct GComponent));

    if(component == NULL) {
        GError("GComponentInit() : failed to allocate memory\n");
        return NULL;
    }

    component->rendering_function = rendering_function;
    component->is_component_visible = true;
    component->is_component_rendered = false;
    component->is_pos_absolute = false;

    return component;
}


void GComponentSetDimension(void* component, GDimension dimension) {
    ((GComponent) component)->dimension = dimension;
}


void GComponentSetPosition(void* component, GPosition position) {
    ((GComponent) component)->position = position;
}


GDimension GComponentGetDimension(void* component) {
    return ((GComponent) component)->dimension;
}


GPosition GComponentGetPosition(void* component) {
    return ((GComponent) component)->position;
}


bool GComponentRendered(const void* component) {
    return ((GComponent) component)->is_component_rendered;
}


bool GComponentVisible(const void* component) {
    return ((GComponent) component)->is_component_visible;
}


void GComponentSetVisible(void* component, bool is_component_visible) {
    ((GComponent) component)->is_component_visible = is_component_visible;
}


void GComponentSetParentPanel(void* component, GPanel panel) {
    ((GComponent) component)->parent_panel = panel;
}


GRenderingFunction GComponentGetRenderingFunction(const void* component) {
    return ((GComponent) component)->rendering_function;
}


GComponentType GComponentGetType(const void* component) {
    return ((GComponent) component)->component_type;
}


GPanel GComponentGetParentPanel(void* component) {
    return ((GComponent) component)->parent_panel;
}


GWindow GComponentGetWindow(void* component) {
    return GPanelGetWindow(GComponentGetParentPanel(component));
}


bool GComponentHovered(SDL_Event* event, void* component) {

    GComponent gcomponent = (GComponent) component;

    GPosition component_position = gcomponent->position;

    GDimension component_dimension = gcomponent->dimension;

    GPosition cursor_position;

    SDL_GetMouseState(&cursor_position.x, &cursor_position.y);
    
    if(cursor_position.x >= component_position.x && cursor_position.y >= component_position.y 
        && cursor_position.x <= component_position.x + component_dimension.width && cursor_position.y <= component_position.y + component_dimension.height)
        return true;

    return false;
}


bool GComponentLeftClicked(SDL_Event* event, void* component) {
    return GComponentHovered(event, component) && GMouseLeftClicked(event);
}


bool GComponentRightClicked(SDL_Event* event, void* component) {
    return GComponentHovered(event, component) && GMouseRightClicked(event);
}


bool GMouseLeftClicked(SDL_Event* event) {
    return event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT;
}


bool GMouseLeftPressed(SDL_Event* event) {
    return event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT;
}


bool GMouseRightClicked(SDL_Event* event) {
    return event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_RIGHT;
}


bool GMouseRightPressed(SDL_Event* event) {
    return event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT;
}


GDimension GDimensionInit(uint32_t width, uint32_t height) {
    GDimension dimension = {width, height};
    return dimension;
}


GPosition GPositionInit(int x, int y) {
    GPosition position = {x, y};
    return position;
}


GColor GColorInit(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    GColor color = {r, g, b, a};
    return color;
}


GColorYUV GColorYUVInit(float y, float u, float v) {
    GColorYUV color = {y, u, v};
    return color;
}


GColorYUV GColorToYUV(GColor color_rgb) {
    GColorYUV color_yuv = {
        0.299 * color_rgb.r + 0.587 * color_rgb.g + 0.114 * color_rgb.b,
        0.492 * (color_rgb.b - color_yuv.y),
        0.877 * (color_rgb.r - color_yuv.y)
    };
    return color_yuv;
}


GColor GColorYUVToRGB(GColorYUV color_yuv) {

    int16_t r = roundf(color_yuv.y + 1.13983 * color_yuv.v);
    int16_t g = roundf(color_yuv.y - 0.39465 * color_yuv.u - 0.5806 * color_yuv.v);
    int16_t b = roundf(color_yuv.y + 2.03211 * color_yuv.u);

    if(r > 255)
        r = 255;
    if(r < 0)
        r = 0;

    if(g > 255)
        g = 255;
    if(g < 0)
        g = 0;

    if(b > 255)
        b = 255;
    if(b < 0)
        b = 0;

    GColor color_rgb = {r, g, b};

    return color_rgb;
}


GColor GColorSetLuminance(GColor color, float multiplicator) {

    uint8_t a = color.a;

    GColorYUV yuv = GColorToYUV(color);

    yuv.y *= multiplicator;

    GColor modified = GColorYUVToRGB(yuv);
    modified.a = a;

    return modified;
}


void GComponentAdaptDimension(void* component) {
    
    GComponent gcomponent = (GComponent) component;

    GComponent parent_panel = (GComponent) gcomponent->parent_panel;

    gcomponent->texture_dimension.x = gcomponent->position.x;

    gcomponent->texture_dimension.y = gcomponent->position.y;

    if(parent_panel == NULL)
        return;

    if(gcomponent->dimension.width > parent_panel->texture_dimension.w)
        gcomponent->texture_dimension.w = parent_panel->texture_dimension.w;
    else
        gcomponent->texture_dimension.w = gcomponent->dimension.width;
    
    if(gcomponent->dimension.height > parent_panel->dimension.height)
        gcomponent->texture_dimension.h = parent_panel->texture_dimension.h;   
    else
         gcomponent->texture_dimension.h = gcomponent->dimension.height;
}


void GComponentSetTextureDimension(void* component, SDL_Rect dimension) {
    ((GComponent) component)->texture_dimension = dimension;
}


SDL_Rect GComponentGetTextureDimension(void* component) {
    return ((GComponent) component)->texture_dimension;
}


void GComponentDestroy(void* component) {
    GDestroyFunction function = ((GComponent) component)->destroy_function;
    function(component);
}


uint8_t GError(const char* message) {
    SDL_SetError("%s", message);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s", SDL_GetError());
    return G_OPERATION_ERROR;
}