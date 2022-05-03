#ifndef __LIST_H__
#define __LIST_H__

#include "components_utils.h"

#define LIST_DEFAULT_PADDING 5

#define LIST_ORIENTATION_HORIZONTAL 1
#define LIST_ORIENTATION_VERTICAL 2

typedef struct s_list* List;

List init(Color* color, uint8_t list_orientation, uint8_t type, uint8_t constraint);

// Returns -1 if error, else 0
uint8_t push(List list, Element element);

Element get(List list, uint32_t index);

uint32_t get_size(List list);

uint8_t replace(List list, void* element_old, void* element_new);

uint8_t replace_at(List list, uint32_t old_elem_index, void* element_new);

uint8_t insert_at(List list, uint32_t index, Element element);

uint8_t pop(List list);

// Returns -1 if error, else 0
uint8_t del(List list, void* element);

// Returns -1 if error, else 0
uint8_t del_at(List list, uint32_t index);

void destroy_list(List list);

#endif