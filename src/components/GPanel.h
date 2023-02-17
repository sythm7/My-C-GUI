#ifndef __GPANEL_H__
#define __GPANEL_H__

/**
 * @file panel.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a GPanel component.
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../utils/GComponentUtils.h"
#include "GLabel.h"
#include "GList.h"
#include "GTextfield.h"
#include "GButton.h"
#include "GImage.h"

typedef struct GWindow* GWindow;

/**
 * @brief GPanel component. \n
 * GPanel are containers for the components, and can also contain children GPanel
 * 
 */
typedef struct GPanel* GPanel;

/**
 * @brief Create a GPanel component. \n
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @return GPanel 
 */
GPanel GPanelInit();

/**
 * @brief Set the GPanel background color
 * 
 * @param color 
 */
void GPanelSetColor(GPanel panel, GColor color);

/**
 * @brief Set a visible border around a GPanel
 * 
 * @param panel 
 * @param size 
 * @param top 
 * @param bottom 
 * @param left 
 * @param right 
 */
void GPanelSetBorder(GPanel panel, uint8_t size, bool top, bool bottom, bool left, bool right);

/**
 * @brief Add a child GPanel into a GPanel. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param panel 
 * @param child_panel 
 * @return uint8_t 
 */
uint8_t GPanelAddChild(GPanel panel, GPanel child_panel);

/**
 * @brief Add a GComponent into a GPanel. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param panel 
 * @param component 
 * @return uint8_t 
 */
uint8_t GPanelAddComponent(GPanel panel, void* component);

/**
 * @brief Get the GWindow affected to a GPanel.
 * 
 * @param panel 
 * @return GWindow 
 */
GWindow GPanelGetWindow(const GPanel panel);


/**
 * @brief Get the GComponent list of a GPanel
 * 
 * @param panel 
 * @return GComponent* 
 */
GComponent* GPanelGetComponentList(const GPanel panel);

/**
 * @brief Get the GComponent list size of a GPanel
 * 
 * @param panel 
 * @return uint32_t 
 */
uint32_t GPanelGetComponentListSize(const GPanel panel);

/**
 * @brief Get the children GPanel list of a GPanel
 * 
 * @param panel 
 * @return GPanel* 
 */
GPanel* GPanelGetChildList(const GPanel panel);

/**
 * @brief Get the children GPanel list size of a GPanel
 * 
 * @param panel 
 * @return uint32_t 
 */
uint32_t GPanelGetChildListSize(const GPanel panel);

/**
 * @brief Free the memory used by a GPanel
 * 
 * @param component 
 */
void GPanelDestroy(void* component);


#endif