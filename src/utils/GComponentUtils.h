#ifndef __GCOMPONENTUTILS_H__
#define __GCOMPONENTUTILS_H__


/**
 * @file GComponentUtils.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a component. \n
 * The component data type has to be used only if you need to create custom components. Otherwise use existing components (example : GTextfield).
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
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define G_OPERATION_ERROR 0
#define G_OPERATION_SUCCESS 1


typedef struct GWindow *GWindow;
typedef struct GPanel *GPanel;


/**
 * @brief GComponent data type
 */
typedef struct GComponent* GComponent;


/**
 * @brief GRenderingFunction type. \n
 * Used to specify the rendering process of a custom component
 * 
 */
typedef uint8_t (*GRenderingFunction)(void* component);

/**
 * @brief GEventFunction type. \n
 * Used to specify the action executed when an event is triggered
 * 
 */
typedef int (*GEventFunction)(void* data, SDL_Event* event);

/**
 * @brief GDestroyFunction type. \n
 * Used to specify the destruction process of a custom component
 * 
 */
typedef void (*GDestroyFunction)(void* component);

/**
 * @brief Values used to determine and check the type of a component
 * 
 */
typedef enum {
    COMPONENT_NONE,
    COMPONENT_PANEL,
    COMPONENT_LIST,
    COMPONENT_BUTTON,
    COMPONENT_TEXTFIELD,
    COMPONENT_IMAGE,
    COMPONENT_LABEL
} GComponentType;

/**
 * @brief GDimension data type
 * 
 */
typedef struct {
    int width;
    int height;
} GDimension;

/**
 * @brief GPosition data type
 * 
 */
typedef struct {
    int x;
    int y;
} GPosition;

/**
 * @brief GColor data type
 * 
 */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} GColor;

/**
 * @brief YUV GColor space data type
 * 
 */
typedef struct {
    float y;
    float u;
    float v;
} GColorYUV;

/**
 * @brief Transform an RGB color space to a YUV color space
 * 
 * @param color_rgb
 * @return GColorYUV 
 */
GColorYUV GColorToYUV(GColor color_rgb);

/**
 * @brief Transform a YUV color space to an RGB color space
 * 
 * @param color_yuv
 * @return GColor 
 */
GColor GColorYUVToRGB(GColorYUV color_yuv);


/**
 * @brief Apply a custom luminance to an existing color
 * 
 * @param color 
 * @param multiplicator 
 * @return GColor 
 */
GColor GColorSetLuminance(GColor color, float multiplicator);

/**
 * @brief @brief Create a GComponent (Use only to make a custom component, otherwise, use existing components. Example : GTextfield). \n
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError().
 * 
 * @param rendering_function 
 * @param destroy_function 
 * @param type
 * @return GComponent 
 */
GComponent GComponentInit(GRenderingFunction rendering_function, GDestroyFunction destroy_function, GComponentType type);

/**
 * @brief Check if a component has already been rendered on the screen. \n
 * If a component has been modified before between two window renderings, GComponentRendered() will return false. 
 * 
 * @param component 
 * @return true 
 * @return false 
 */
bool GComponentRendered(const void* component);

/**
 * @brief Check if a component is visible on the screen
 * 
 * @param component 
 * @return true 
 * @return false 
 */
bool GComponentVisible(const void* component);

/**
 * @brief Configure if a component should be visible or not. \n
 * By default, GComponentVisible is set to true.
 * 
 * @param component 
 * @param GComponentVisible 
 */
void GComponentSetVisible(void* component, bool GComponentVisible);

/**
 * @brief Get the parent GPanel of a component. \n
 * NULL if the component is not affected to any GPanel
 * 
 * @param component 
 * @return GPanel 
 */
GPanel GComponentGetParentPanel(void* component);

/**
 * @brief Get the parent GWindow of a component \n
 * NULL if the component is not affected to any GWindow
 * 
 * @param component 
 * @return GWindow 
 */
GWindow GComponentGetWindow(void* component);

/**
 * @brief Get the GDimension of a component
 * 
 * @param component 
 * @return GDimension 
 */
GDimension GComponentGetDimension(void* component);

/**
 * @brief Get the GPosition of a component
 * 
 * @param component 
 * @return GPosition 
 */
GPosition GComponentGetPosition(void* component);

/**
 * @brief Set the GDimension of a component
 * 
 * @param component 
 * @param dimension 
 */
void GComponentSetDimension(void* component, GDimension dimension);

/**
 * @brief Set the GPosition of a component
 * 
 * @param component 
 * @param position 
 */
void GComponentSetPosition(void* component, GPosition position);

/**
 * @brief Get the GRenderingFunction of the component. \n
 * The GRenderingFunction inside a GComponent is used to render this GComponent.
 * 
 * @param component 
 * @return GRenderingFunction 
 */
GRenderingFunction GComponentGetRenderingFunction(const void* component);

/**
 * @brief Get the GComponent type
 * 
 * @param component 
 * @return GComponentType 
 */
GComponentType GComponentGetType(const void* component);

/**
 * @brief Check if the mouse cursor is hovering a GComponent.
 * 
 * @param event 
 * @param component 
 * @return true 
 * @return false 
 */
bool GComponentHovered(SDL_Event* event, void* component);

/**
 * @brief Check if the component has been left clicked
 * 
 * @param event 
 * @param component 
 * @return true 
 * @return false 
 */
bool GComponentLeftClicked(SDL_Event* event, void* component);

/**
 * @brief Check if the component has been right clicked
 * 
 * @param event 
 * @param component 
 * @return true 
 * @return false 
 */
bool GComponentRightClicked(SDL_Event* event, void* component);


/**
 * @brief Check if the left mouse button has been clicked (released)
 * 
 * @param event 
 * @return true 
 * @return false 
 */
bool GMouseLeftClicked(SDL_Event* event);

/**
 * @brief Check if the left mouse button has been pressed
 * 
 * @param event 
 * @return true 
 * @return false 
 */
bool GMouseLeftPressed(SDL_Event* event);

/**
 * @brief Check if the right mouse button has been clicked (released)
 * 
 * @param event 
 * @return true 
 * @return false 
 */
bool GMouseRightClicked(SDL_Event* event);

/**
 * @brief Check if the right mouse button has been pressed
 * 
 * @param event 
 * @return true 
 * @return false 
 */
bool GMouseRightPressed(SDL_Event* event);

/**
 * @brief Add an event listener to a component or to another structure to execute a GEventFunction when an event is triggered. \n
 * The data will be passed into GEventFunction arguments. \n
 * The data is generally a GComponent, but it can be whatever you want.
 * 
 * @param event_function 
 * @param data 
 */
uint8_t GComponentAddListener(GEventFunction event_function, void* component);

/**
 * @brief Create a dimension with the given width and height
 * 
 * @param width 
 * @param height 
 * @return GDimension 
 */
GDimension GDimensionInit(uint32_t width, uint32_t height);

/**
 * @brief Create a position. \n
 * x from left to right, y from top to bottom 
 * 
 * @param x 
 * @param y 
 * @return GPosition 
 */
GPosition GPositionInit(int x, int y);

/**
 * @brief Create a RGB color. \n
 * r : red, g : green, b : blue, a : alpha
 * 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 * @return GColor 
 */
GColor GColorInit(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Create a YUV color. \n
 * y : luminance, u and v : chrominance
 * 
 * @param y 
 * @param u 
 * @param v 
 * @return GColorYUV
 */
GColorYUV GColorYUVInit(float y, float u, float v);

/**
 * @brief Free the memory used by a component \n
 * When you destroy a GWindow with GWindowDestroy(), this function is automatically called, which means your component will not be initialized anymore after a GWindow destruction. \n
 * If you call this function, all the components contained into the given component will be destroyed.
 * 
 * @param component 
 */
void GComponentDestroy(void* component);

/**
 * @brief Set an error that returns G_OPERATION_ERROR and prints the message in argument. \n
 * The error message can be recovered anywhere in your program, using SDL_GetError().
 * @param message 
 * @return uint8_t 
 */
uint8_t GError(const char* message);

#endif