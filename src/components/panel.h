#ifndef __PANEL_H__
#define __PANEL_H__

/**
 * @file panel.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a Panel component.
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "components_utils.h"
#include "label.h"
#include "list.h"
#include "textfield.h"

typedef struct Layout* Layout;
typedef struct Window* Window;

/**
 * @brief Panel component.
 * Panels are containers for the components, and can also contain children panels that contains other components or/and other panels themselves
 * 
 */
typedef struct Panel* Panel;

/**
 * @brief Create a Panel component.
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @return Panel 
 */
Panel init_panel();

/**
 * @brief Add a panel into another panel.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param panel 
 * @param child_panel 
 * @return uint8_t 
 */
uint8_t add_panel(Panel panel, Panel child_panel);

/**
 * @brief Add a component into a panel.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param panel 
 * @param component 
 * @return uint8_t 
 */
uint8_t add_component(Panel panel, Component component);

/**
 * @brief Set the panel dimension
 * 
 * @param panel 
 * @param dimension 
 */
void set_panel_dimension(Panel panel, Dimension dimension);

/**
 * @brief Set the panel position
 * 
 * @param panel 
 * @param position 
 */
void set_panel_position(Panel panel, Position position);


Window get_parent_window(Panel panel);


/**
 * @brief Get the components list of a panel
 * 
 * @param panel 
 * @return Component* 
 */
Component* get_components(const Panel panel);

/**
 * @brief Get the components list size of a panel
 * 
 * @param panel 
 * @return uint32_t 
 */
uint32_t get_components_size(const Panel panel);

/**
 * @brief Get the children panels list of a panel
 * 
 * @param panel 
 * @return Panel* 
 */
Panel* get_children_panels(const Panel panel);

/**
 * @brief Get the children panels list size of a panel
 * 
 * @param panel 
 * @return uint32_t 
 */
uint32_t get_children_size(const Panel panel);

#endif