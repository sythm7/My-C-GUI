#ifndef __GWINDOW_H__
#define __GWINDOW_H__

/**
 * @file GWindow.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a GWindow.
 * The window is used to render all the components contained in a specified panel.
 * 
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../components/GPanel.h"

/**
 * @brief GWindow component
 * 
 */
typedef struct GWindow* GWindow;

/**
 * @brief Create a GWindow with the given title, background color and flags. \n
 * A NULL pointer is returned if an error is encountered. \n
 * \n
 * List of the flags (from the SDL library) : \n
 * SDL_WINDOW_FULLSCREEN         < fullscreen window \n
 * SDL_WINDOW_OPENGL             < window usable with OpenGL context \n
 * SDL_WINDOW_SHOWN              < window is visible \n
 * SDL_WINDOW_HIDDEN             < window is not visible \n
 * SDL_WINDOW_BORDERLESS         < no window decoration \n
 * SDL_WINDOW_RESIZABLE          < window can be resized \n
 * SDL_WINDOW_MINIMIZED          < window is minimized \n
 * SDL_WINDOW_MAXIMIZED          < window is maximized \n
 * SDL_WINDOW_MOUSE_GRABBED      < window has grabbed mouse input \n
 * SDL_WINDOW_INPUT_FOCUS        < window has input focus \n
 * SDL_WINDOW_MOUSE_FOCUS        < window has mouse focus \n
 * SDL_WINDOW_FULLSCREEN_DESKTOP < fullscreen window at the current desktop resolution \n
 * SDL_WINDOW_FOREIGN            < window not created by SDL \n
 * SDL_WINDOW_ALLOW_HIGHDPI      < window should be created in high-DPI mode if supported. On macOS NSHighResolutionCapable must be set true in the application's Info.plist for this to have any effect. \n
 * SDL_WINDOW_MOUSE_CAPTURE      < window has mouse captured (unrelated to MOUSE_GRABBED) \n
 * SDL_WINDOW_ALWAYS_ON_TOP      < window should always be above others \n
 * SDL_WINDOW_SKIP_TASKBAR       < window should not be added to the taskbar \n
 * SDL_WINDOW_UTILITY            < window should be treated as a utility window \n
 * SDL_WINDOW_TOOLTIP            < window should be treated as a tooltip \n
 * SDL_WINDOW_POPUP_MENU         < window should be treated as a popup menu \n
 * SDL_WINDOW_KEYBOARD_GRABBED   < window has grabbed keyboard input \n
 * SDL_WINDOW_VULKAN             < window usable for Vulkan surface \n
 * SDL_WINDOW_METAL              < window usable for Metal view \n
 * SDL_WINDOW_INPUT_GRABBED      < equivalent to SDL_WINDOW_MOUSE_GRABBED for compatibility \n
 * 
 * @param title 
 * @param background_color 
 * @param flags
 * @return GWindow
 */
GWindow GWindowInit(const char* title, GColor background_color, SDL_WindowFlags flags);

void GWindowWait(GWindow window);

/**
 * @brief Set the window dimension.
 * 
 * @param window 
 * @param dimension 
 */
void GWindowSetDimension(GWindow window, GDimension dimension);

/**
 * @brief Center the window position relative to the screen.
 * 
 * @param window 
 */
void GWindowCenterPosition(GWindow window);

/**
 * @brief Center the window position relative to another window.
 * 
 * @param window_to_center 
 * @param other_window 
 */
void GWindowCenterPositionFromWindow(GWindow window_to_center, GWindow other_window);

/**
 * @brief Render the components from the window's panel and show them on the screen. \n
 * G_OPERATION_ERROR is returned if an error is encountered (call SDL_GetError() for more information)
 * 
 * @param window 
 * @return uint8_t 
 */
uint8_t GWindowDisplay(GWindow window);

/**
 * @brief Set the window background color.
 * 
 * @param window 
 * @param color 
 */
void GWindowSetBackgroundColor(GWindow window, GColor color);

/**
 * @brief Get the window dimension.
 * 
 * @param window 
 * @return GDimension 
 */
GDimension GWindowGetDimension(GWindow window);

/**
 * @brief Get the window position.
 * 
 * @param window 
 * @return GPosition 
 */
GPosition GWindowGetPosition(GWindow window);

/**
 * @brief Attach the main panel to a window. \n
 * A window can contain only 1 panel. (A panel can contain multiple panels). \n
 * If no panel is specified for a window, no component will be rendered by this window.
 * 
 * @param window
 * @param panel
 */
void GWindowSetPanel(GWindow window, GPanel panel);

/**
 * @brief Check if a GWindow has the input focus.
 * 
 * @param window 
 * @return true 
 * @return false 
 */
bool GWindowFocused(GWindow window);

/**
 * @brief Get the SDL_Window* from a GWindow. \n
 * You need to refer to the SDL documentation if you want to know more about SDL_Window.
 * 
 * @param window 
 * @return SDL_Window* 
 */
SDL_Window* GWindowGetSDL_Window(GWindow window);

/**
 * @brief Get the SDL_Renderer* from a GWindow. \n
 * Useful to make renders for custom components. \n
 * You need to refer to the SDL documentation if you want to know more about SDL_Renderer.
 * 
 * @param window 
 * @return SDL_Renderer* 
 */
SDL_Renderer* GWindowGetSDL_Renderer(GWindow window);

/**
 * @brief Close the window.
 * 
 * @param window 
 * @return uint8_t 
 */
uint8_t GWindowClose(GWindow window);

/**
 * @brief Free the memory used by a window.
 * 
 * @param window 
 */
void GWindowDestroy(GWindow window);

#endif