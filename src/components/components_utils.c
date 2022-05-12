#include "components_utils.h"

struct Component {
    RenderingFunction rendering_function;
    DestroyFunction destroy_function;
    ComponentType component_type;
    Panel parent_panel;
    Dimension dimension;
    Position position;
    bool is_visible;
    bool is_rendered;
    bool is_pos_absolute;
};

Window get_parent_window(Panel panel);

Component init_component(RenderingFunction rendering_function) {

    Component component = malloc(sizeof(struct Component));

    if(component == NULL) {
        set_error("init_component() : failed to allocate memory\n");
        return NULL;
    }

    component->rendering_function = rendering_function;
    component->is_visible = true;
    component->is_rendered = false;
    component->is_pos_absolute = false;

    return component;
}


bool is_rendered(const Component component) {

    return component->is_rendered;
}


bool is_visible(const Component component) {

    return component->is_visible;
}


void set_visible(Component component, bool is_visible) {

    component->is_visible = is_visible;
}


void set_parent_panel(Component component, Panel panel) {
    component->parent_panel = panel;
}


RenderingFunction get_rendering_function(const Component component) {

    return component->rendering_function;
}


ComponentType get_component_type(const Component component) {
    return component->component_type;
}


Panel get_parent_panel(Component component) {
    return component->parent_panel;
}


Window get_window(Component component) {
    return get_parent_window(get_parent_panel(component));
}


Dimension init_dimension(uint32_t width, uint32_t height) {
    Dimension dimension;
    dimension.width = width;
    dimension.height = height;
    return dimension;
}


Position init_position(int x, int y) {
    Position position;
    position.x = x;
    position.y = y;
    return position;
}


Color init_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}


void destroy_component(Component component) {
    DestroyFunction function = component->destroy_function;
    function(component);
}


uint8_t set_error(const char* message) {
    SDL_SetError(message);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, SDL_GetError());
    return OPERATION_ERROR;
}