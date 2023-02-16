#ifndef __GLIST_H__
#define __GLIST_H__

/**
 * @file list.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a GList component
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../utils/GComponentUtils.h"

/**
 * @brief list.h definitions
 * 
 */
#define LIST_DEFAULT_PADDING 5
#define LIST_ORIENTATION_HORIZONTAL 1
#define LIST_ORIENTATION_VERTICAL 2

/**
 * @brief GList component. \n
 * GList components are used to store other components and to display them as a list format. \n
 * Components added to a GList need to all have the same GComponentType and need a GRenderingFunction to be displayed as an element of the GList.
 * 
 */
typedef struct GList* GList;

/**
 * @brief Create a GList component. \n
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param color 
 * @param list_orientation 
 * @param type 
 * @return GList 
 */
GList GListInit(GColor color, uint8_t list_orientation, GComponentType type);

/**
 * @brief Add an element to a list. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param element 
 * @return uint8_t 
 */
uint8_t GListAddComponent(GList list, void* component);

/**
 * @brief Get the list element at the given index. \n
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param index 
 * @return GComponent 
 */
GComponent GListGetComponentAt(GList list, uint32_t index);

/**
 * @brief Get the list size
 * 
 * @param list 
 * @return uint32_t 
 */
uint32_t GListGetSize(GList list);

/**
 * @brief Replace a given element of a list by a new one. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param element_old 
 * @param element_new 
 * @return uint8_t 
 */
uint8_t GListReplaceComponent(GList list, void* old_component, void* new_component);

/**
 * @brief Replace the element of the given index by a new one. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param old_elem_index 
 * @param element_new 
 * @return uint8_t 
 */
uint8_t GListReplaceComponentAt(GList list, uint32_t old_component_index, void* new_component);

/**
 * @brief Insert an element at the given index. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param index 
 * @param element 
 * @return uint8_t 
 */
uint8_t GListInsertComponentAt(GList list, uint32_t index, void* component);

/**
 * @brief Delete the last element of a list. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @return uint8_t 
 */
uint8_t GListDelLastComponent(GList list);

/**
 * @brief Delete the given element from the list if it exists. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param element 
 * @return uint8_t 
 */
uint8_t GListDelComponent(GList list, void* component);

/**
 * @brief Delete the element of the given index. \n
 * G_OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param index 
 * @return uint8_t 
 */
uint8_t GListDelComponentAt(GList list, uint32_t index);

#endif