#include "components_utils.h"

struct s_element {
    void* content;
    uint8_t type;
    uint8_t return_code;
};

struct s_component {
    void* content;
    ComponentType type;
    bool is_rendered;
    bool is_visible;
    rendering_function rendering_function;
};

Component init_component(void* content, uint8_t type, rendering_function rendering_function) {
    Component component = malloc(sizeof(struct s_component));
    component->content = content;
    component->type = type;
    component->rendering_function = rendering_function;
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

rendering_function get_rendering_function(Component component) {
    if(component == NULL)
        printf("COMPONENT NULL\n");
    return component->rendering_function;
}

ComponentType get_component_type(const Component component) {
    return component->type;
}

void* get_component_content(Component component) {
    return component->content;
}


Dimension init_dimension(uint32_t width, uint32_t height) {
    Dimension dimension;
    dimension.width = width;
    dimension.height = height;
    return dimension;
}

Position init_position(uint32_t x, uint32_t y) {
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

Element init_element(void* content, uint8_t type) {
    Element element = malloc(sizeof(struct s_element));
    element->content = content;
    element->type = type;
    element->return_code = OPERATION_SUCCESS;

    return element;
}

void* get_element_content(const Element element) {
    return element->content;
}

uint8_t get_return_code(const Element element) {
    return element->return_code;
}

uint8_t get_element_type(Element element) {
    return element->type;
}

void set_return_code(Element element, uint8_t return_code) {
    element->return_code = return_code;
}

void destroy_element(Element element) {
    free(element);
}

void destroy_component(Component component) {
    free(component);
}