#include "list.h"
#include <stdio.h>

#define MIN_LIST_SIZE 5
#define SHORT_LIST_SIZE 15
#define MEDIUM_LIST_SIZE 30
#define BIG_LIST_SIZE 100
#define VERY_BIG_LIST_SIZE 1000
#define GIANT_LIST_SIZE 100000

struct List {
    RenderingFunction rendering_function;
    DestroyFunction destroy_function;
    ComponentType component_type;
    Panel parent_panel;
    Dimension dimension;
    Position position;
    bool is_visible;
    bool is_rendered;
    bool is_pos_absolute;
    SDL_Texture* texture;
    Component* elems;
    ComponentType type;
    uint32_t size;
    uint32_t allocated_size;
    uint8_t orientation;
    int padding;
};

uint8_t render_list(Component component);

void destroy_list(Component component);

uint8_t reallocate_add(List list);

uint8_t reallocate_del(List list);

List init_list(Color color, uint8_t list_orientation, ComponentType type) {

    Dimension dimension = init_dimension(0, 0);

    List list = malloc(sizeof(struct List));

    if(list == NULL) {
        set_error("init_list() : failed to allocate memory\n");
        return NULL;
    }

    list->allocated_size = 0;

    list->elems = malloc(list->allocated_size * sizeof(Component));

    if(list->elems == NULL) {
        set_error("init_list() : failed to allocate memory\n");
        return NULL;
    }

    list->rendering_function = &render_list;
    list->destroy_function = &destroy_list;
    list->is_rendered = false;
    list->is_visible = true;
    list->is_pos_absolute = false;

    list->size = 0;
    list->texture = NULL;
    list->dimension = dimension;

    list->orientation = list_orientation;
    list->padding = LIST_DEFAULT_PADDING;

    return list;
}


uint8_t add_list_element(List list, Component element) {

    if(list->type != get_component_type(element))
        return set_error("add_list_element() : failed to add element. The element doesn't have the same type as the list.\n");

    if(reallocate_add(list) == OPERATION_ERROR)
        return set_error("add_list_element() : failed to reallocate memory\n");    

    list->elems[list->size++] = element;

    return OPERATION_SUCCESS;
}


Component get_list_element(List list, uint32_t index) {
    
    if(index >= list->size) {
        set_error("get_list_element() : list size lower or equal to the given index. Can't get element\n");
        return NULL;
    }
    
    return (Component) list->elems[index];
}


uint32_t get_list_size(List list) {
    return list->size;
}


uint8_t insert_list_element_at(List list, uint32_t index, Component element) {

    if(index >= list->size)
        return set_error("insert_list_element_at() : list size lower or equal to the given index. Can't insert element\n");

    // TODO


    return OPERATION_SUCCESS;
}


uint8_t del_list_element(List list, void* element) {

    bool found = false;
    uint8_t pos = 0;

    for(; !found && pos < list->size; pos++)
        if(list->elems[pos] == element) 
            found = true;

    if(!found)
        return set_error("del_list_element() : element not found in list. Can't delete element\n");

    uint8_t result = del_list_element_at(list, pos);

    if(result == OPERATION_ERROR)
        return set_error("Call from del_list_element()\n");

    return OPERATION_SUCCESS;
}


uint8_t del_list_element_at(List list, uint32_t index) {

    if(index >= list->size)
        return set_error("del_list_element_at() : list size lower or equal to the given index. Can't delete element\n");


    for(int pos = index; pos < (list->size)-1; pos++) {
        list->elems[pos] = list->elems[pos+1];
    }

    list->size--;

    if(reallocate_del(list) == OPERATION_ERROR)
        return set_error("del_list_element_at() : failed to reallocate memory\n");

    return OPERATION_SUCCESS;
}


uint8_t del_last_list_element(List list) {

    uint8_t result = del_list_element_at(list, list->size);

    if(result == OPERATION_ERROR)
        return set_error("Call from del_last_list_element()\n");

    return OPERATION_SUCCESS;
}


uint8_t reallocate_add(List list) {

    if(list->size < list->allocated_size)
        return OPERATION_SUCCESS;

    else if(list->size >= GIANT_LIST_SIZE)
        list->allocated_size += GIANT_LIST_SIZE;

    else if(list->size >= VERY_BIG_LIST_SIZE)
        list->allocated_size += VERY_BIG_LIST_SIZE; 

    else if(list->size >= BIG_LIST_SIZE)
        list->allocated_size += BIG_LIST_SIZE;

    else if(list->size >= MEDIUM_LIST_SIZE)
        list->allocated_size += MEDIUM_LIST_SIZE;

    else if(list->size >= SHORT_LIST_SIZE)
        list->allocated_size += SHORT_LIST_SIZE;

    else
        list->allocated_size += 2*MIN_LIST_SIZE;

    Component* tempPtr = realloc(list->elems, list->allocated_size * sizeof(Component));

    if(tempPtr == NULL)
        return OPERATION_ERROR;

    list->elems = tempPtr;

    return OPERATION_SUCCESS;
}


uint8_t reallocate_del(List list) {

    if(list->size <= GIANT_LIST_SIZE && list->allocated_size > GIANT_LIST_SIZE)
        list->allocated_size = GIANT_LIST_SIZE;
    else if(list->size >= VERY_BIG_LIST_SIZE && list->allocated_size > VERY_BIG_LIST_SIZE)
        list->allocated_size = VERY_BIG_LIST_SIZE;
    else if(list->size >= BIG_LIST_SIZE && list->allocated_size > BIG_LIST_SIZE)
        list->allocated_size = BIG_LIST_SIZE;
    else if(list->size >= MEDIUM_LIST_SIZE && list->allocated_size > MEDIUM_LIST_SIZE)
        list->allocated_size = MEDIUM_LIST_SIZE;
    else if(list->size >= SHORT_LIST_SIZE && list->allocated_size > SHORT_LIST_SIZE)
        list->allocated_size = SHORT_LIST_SIZE;
    else
        return OPERATION_SUCCESS;

    Component* tempPtr = realloc(list->elems, list->allocated_size);

    if(tempPtr == NULL)
        return OPERATION_ERROR;

    list->elems = tempPtr;

    return OPERATION_SUCCESS;
}

uint8_t render_list(Component component) {

    // TODO
    return OPERATION_SUCCESS;
}

void destroy_list(Component component) {

    List list = (List) component;

    if(list->texture != NULL)
        SDL_DestroyTexture(list->texture);

    for(int i = 0; i < list->size; i++) 
        destroy_component(list->elems[i]);

    free(list->elems);
    free(list);
}