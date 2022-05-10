#ifndef __COMPONENTS_UTILS_H__
#define __COMPONENTS_UTILS_H__

#include <stdint.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define OPERATION_ERROR 0
#define OPERATION_SUCCESS 1

typedef struct s_component* Component;

typedef void (*rendering_function)(void* window, Component component);

typedef enum {
    COMPONENT_NONE,
    COMPONENT_LIST,
    COMPONENT_BUTTON,
    COMPONENT_TEXT_FIELD,
    COMPONENT_IMAGE,
    COMPONENT_LABEL
} ComponentType;

typedef enum {
    false, 
    true
} bool;

typedef struct {
    uint32_t width;
    uint32_t height;
} Dimension;

typedef struct {
    uint32_t x;
    uint32_t y;
} Position;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

/* ELEMENT DATA STRUCTURE */

typedef struct s_element *Element;

Element init_element(void* content, uint8_t type);

void* get_element_content(const Element element);

uint8_t get_return_code(const Element element);

uint8_t get_element_type(const Element element);

void set_return_code(Element element, uint8_t return_code);

void destroy_element(Element element);

/* END ELEMENT DATA STRUCTURE */

Component init_component(void* content, uint8_t type, void (*render_function)(void* window, Component component));

void destroy_component(Component component);

bool is_rendered(const Component component);

bool is_visible(const Component component);

void set_visible(Component component, bool is_visible);

ComponentType get_component_type(const Component component);

void* get_component_content(Component component);

rendering_function get_rendering_function(Component component);

Dimension init_dimension(uint32_t width, uint32_t height);

Position init_position(uint32_t x, uint32_t y);

Color init_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif