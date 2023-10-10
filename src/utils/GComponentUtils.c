#include "GComponentUtils.h"

#define EVENT_LIST_ALLOCATION 5

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
    SDL_Rect src_dimension;
    GEventFunction* event_list;
    int event_list_size;
    int event_list_allocated;
};

GWindow GPanelGetWindow(const GPanel panel);
SDL_Window* GWindowGetSDL_Window(GWindow window);
//int active_window;


GComponent GComponentInit(GRenderingFunction rendering_function, GDestroyFunction destroy_function, GComponentType type) {

    GComponent component = malloc(sizeof(struct GComponent));

    if(component == NULL) {
        GError("GComponentInit() : failed to allocate memory\n");
        return NULL;
    }

    component->rendering_function = rendering_function;
    component->destroy_function = destroy_function;
    component->component_type = type;
    component->parent_panel = NULL;
    component->dimension = GDimensionInit(-1, -1);
    component->position = GPositionInit(0, 0);
    component->is_component_visible = true;
    component->is_component_rendered = false;
    component->is_pos_absolute = false;
    component->texture = NULL;
    component->event_list = NULL;
    component->event_list_size = 0;
    component->event_list_allocated = 0;

    return component;
}


uint8_t GComponentAddListener(GEventFunction event_function, void* component) {

    SDL_AddEventWatch(event_function, component);

    GComponent gcomponent = (GComponent) component;

    if(gcomponent->event_list_size == gcomponent->event_list_allocated) {
        GEventFunction* tempPtr = realloc(gcomponent->event_list, EVENT_LIST_ALLOCATION * sizeof(GEventFunction));

        if(tempPtr == NULL)
            return GError("GComponentAddListener() : Memory allocation error");

        gcomponent->event_list = tempPtr;
        gcomponent->event_list_allocated += EVENT_LIST_ALLOCATION;
    }

    gcomponent->event_list[gcomponent->event_list_size] = event_function;
    gcomponent->event_list_size++;

    return G_OPERATION_SUCCESS;
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
    gcomponent->texture_dimension.w = gcomponent->dimension.width;
    gcomponent->texture_dimension.h = gcomponent->dimension.height;
    gcomponent->src_dimension.x = 0;
    gcomponent->src_dimension.y = 0;

    if(parent_panel == NULL)
        return;

    int area_x = gcomponent->dimension.width + gcomponent->position.x;

    int panel_area_x = parent_panel->texture_dimension.w + parent_panel->position.x;

    int area_y = gcomponent->dimension.height + gcomponent->position.y;

    int panel_area_y = parent_panel->texture_dimension.h + parent_panel->position.y;

    if(area_x > panel_area_x)
        gcomponent->texture_dimension.w -= (area_x - panel_area_x);

    if(area_y > panel_area_y)
        gcomponent->texture_dimension.h -= (area_y - panel_area_y);

    if(gcomponent->texture_dimension.x < parent_panel->texture_dimension.x) {
        int difference = parent_panel->texture_dimension.x - gcomponent->texture_dimension.x;
        gcomponent->texture_dimension.w -= difference;
        gcomponent->texture_dimension.x += difference;
        gcomponent->src_dimension.x += difference;
    }

    if(gcomponent->texture_dimension.y < parent_panel->texture_dimension.y) {
        int difference = parent_panel->texture_dimension.y - gcomponent->texture_dimension.y;
        gcomponent->texture_dimension.h -= difference;
        gcomponent->texture_dimension.y += difference;
        gcomponent->src_dimension.y += difference;
    }

    gcomponent->src_dimension.w = gcomponent->texture_dimension.w;
    gcomponent->src_dimension.h = gcomponent->texture_dimension.h;
}


void GComponentSetTextureDimension(void* component, SDL_Rect dimension) {
    ((GComponent) component)->texture_dimension = dimension;
}


SDL_Rect GComponentGetTextureDimension(void* component) {
    return ((GComponent) component)->texture_dimension;
}


void GComponentDestroy(void* component) {
    GComponent gcomponent = (GComponent) component;

    for(int i = 0; i < gcomponent->event_list_size; i++) {
        SDL_DelEventWatch(gcomponent->event_list[i], gcomponent);
    }

    free(gcomponent->event_list);

    GDestroyFunction function = gcomponent->destroy_function;

    function(component);
}


uint8_t GError(const char* message) {
    SDL_SetError("%s", message);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s", SDL_GetError());
    return G_OPERATION_ERROR;
}