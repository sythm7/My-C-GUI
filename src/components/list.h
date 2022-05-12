#ifndef __LIST_H__
#define __LIST_H__

/**
 * @file list.h
 * @author sythm
 * @brief Contains all the operations to create and manipulate a List component
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "components_utils.h"

/**
 * @brief list.h definitions
 * 
 */
#define LIST_DEFAULT_PADDING 5
#define LIST_ORIENTATION_HORIZONTAL 1
#define LIST_ORIENTATION_VERTICAL 2

/**
 * @brief List component.
 * List components are used to store other components and to display them as a list format.
 * Components added to a List need to all have the same ComponentType and need a RenderingFunction to be displayed as an element of the List.
 * 
 */
typedef struct List* List;

/**
 * @brief Create a List component.
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param color 
 * @param list_orientation 
 * @param type 
 * @return List 
 */
List init_list(Color color, uint8_t list_orientation, ComponentType type);

/**
 * @brief Add an element to a list.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param element 
 * @return uint8_t 
 */
uint8_t add_list_element(List list, Component component);

/**
 * @brief Get the list element at the given index.
 * A NULL pointer is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param index 
 * @return Component 
 */
Component get_list_element(List list, uint32_t index);

/**
 * @brief Get the list size
 * 
 * @param list 
 * @return uint32_t 
 */
uint32_t get_list_size(List list);

/**
 * @brief Replace a given element of a list by a new one.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param element_old 
 * @param element_new 
 * @return uint8_t 
 */
uint8_t replace_list_element(List list, void* element_old, void* element_new);

/**
 * @brief Replace the element of the given index by a new one.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param old_elem_index 
 * @param element_new 
 * @return uint8_t 
 */
uint8_t replace_list_element_at(List list, uint32_t old_elem_index, void* element_new);

/**
 * @brief Insert an element at the given index.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param index 
 * @param element 
 * @return uint8_t 
 */
uint8_t insert_list_element_at(List list, uint32_t index, Component element);

/**
 * @brief Delete the last element of a list.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @return uint8_t 
 */
uint8_t del_last_list_element(List list);

/**
 * @brief Delete the given element from the list if it exists.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * @param list 
 * @param element 
 * @return uint8_t 
 */
uint8_t del_list_element(List list, void* element);

/**
 * @brief Delete the element of the given index.
 * OPERATION_ERROR is returned if an error is encountered, the error detail can be obtained with SDL_GetError()
 * 
 * @param list 
 * @param index 
 * @return uint8_t 
 */
uint8_t del_list_element_at(List list, uint32_t index);

#endif