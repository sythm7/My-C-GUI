#ifndef __COMPONENTS_UTILS_H__
#define __COMPONENTS_UTILS_H__


/**
 * @file components_utils.h
 * @author sythm
 * @brief Contains all the utils for the components.
 * Contains all the operations to create and manipulate a component and an element.
 * The component data type has to be used only if you need to create custom components. Otherwise use existing components (example : Textfield).
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define OPERATION_ERROR 0
#define OPERATION_SUCCESS 1

typedef struct Window *Window;
typedef struct Panel *Panel;

/**
 * @brief Component data type
 */
typedef struct Component* Component;

/**
 * @brief RenderingFunction type.
 * Used to specify the rendering process of a custom component
 * 
 */
typedef uint8_t (*RenderingFunction)(Component component);

/**
 * @brief DestroyFunction type.
 * Used to specify the destruction process of a custom component
 * 
 */
typedef void (*DestroyFunction)(Component component);

/**
 * @brief Values used to determine and check the type of a component
 * 
 */
typedef enum {
    COMPONENT_NONE,
    COMPONENT_PANEL,
    COMPONENT_LIST,
    COMPONENT_BUTTON,
    COMPONENT_TEXT_FIELD,
    COMPONENT_IMAGE,
    COMPONENT_LABEL
} ComponentType;

/**
 * @brief Definition of a classic boolean type
 * 
 */
typedef enum {
    false, 
    true
} bool;

/**
 * @brief Dimension data type
 * 
 */
typedef struct {
    uint32_t width;
    uint32_t height;
} Dimension;

/**
 * @brief Position data type
 * 
 */
typedef struct {
    int x;
    int y;
} Position;

/**
 * @brief Color data type
 * 
 */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

/**
 * @brief Create a Component (Use only to make a custom component, otherwise, use existing components. Example : Textfield).
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * 
 * @param content 
 * @param type 
 * @param render_function 
 * @return Component 
 */
Component init_component(RenderingFunction rendering_function);

/**
 * @brief Check if a component has already been rendered on the screen.
 * If a component has been modified before between two window renderings, is_rendered() will return false.
 * 
 * @param component 
 * @return true 
 * @return false 
 */
bool is_rendered(const Component component);

/**
 * @brief Check if a component is visible on the screen
 * 
 * @param component 
 * @return true 
 * @return false 
 */
bool is_visible(const Component component);

/**
 * @brief Configure if a component should be visible or not.
 * By default, is_visible is set to true.
 * 
 * @param component 
 * @param is_visible 
 */
void set_visible(Component component, bool is_visible);

Panel get_parent_panel(Component component);

Window get_window(Component component);


/**
 * @brief Get the rendering function of the component.
 * The rendering function inside a component is used to render this component.
 * 
 * @param component 
 * @return RenderingFunction 
 */
RenderingFunction get_rendering_function(const Component component);

/**
 * @brief Get the component type
 * 
 * @param component 
 * @return ComponentType 
 */
ComponentType get_component_type(const Component component);

/**
 * @brief Create a dimension
 * 
 * @param width 
 * @param height 
 * @return Dimension 
 */
Dimension init_dimension(uint32_t width, uint32_t height);

/**
 * @brief Create a position.
 * x from left to right, y from top to bottom 
 * 
 * @param x 
 * @param y 
 * @return Position 
 */
Position init_position(int x, int y);

/**
 * @brief Create a color.
 * r : red, g : green, b = blue, a = alpha
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 * @return Color 
 */
Color init_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Free the memory used by a component
 * 
 * @param component 
 */
void destroy_component(Component component);

/**
 * @brief Free the memory used by one or several components
 * 
 * @param label 
 */
void destroy_components(Component components[]);

/**
 * @brief Set an error that returns OPERATION_ERROR and prints the message in argument.
 * The error message can be recovered anywhere in your application, using SDL_GetError().
 * @param message 
 * @return uint8_t 
 */
uint8_t set_error(const char* message);

#endif