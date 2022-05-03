#include "list.h"

#define MIN_LIST_SIZE 5
#define SHORT_LIST_SIZE 15
#define MEDIUM_LIST_SIZE 30
#define BIG_LIST_SIZE 100
#define VERY_BIG_LIST_SIZE 1000
#define GIANT_LIST_SIZE 100000

struct s_list {
    SDL_Texture* texture;
    void** elems;
    uint8_t type;
    uint32_t size;
    uint32_t allocated_size;
    uint8_t orientation;
    Dimension dimension;
    int padding;
};

List init(Color* color, uint8_t list_orientation, uint8_t type, uint8_t constraint) {

    Dimension dimension = init_dimension(0, 0);

    List list = malloc(sizeof(struct s_list));
    list->allocated_size = MIN_LIST_SIZE;
    list->elems = malloc(list->allocated_size * sizeof(void*));
    list->size = 0;
    list->texture = NULL;
    list->dimension = dimension;

    list->orientation = list_orientation;
    list->padding = LIST_DEFAULT_PADDING;

    return list;
}


uint8_t push(List list, Element element) {

    set_return_code(element, OPERATION_SUCCESS);

    if(list->type != get_element_type(element)) {
        set_return_code(element, OPERATION_ERROR);
        return OPERATION_ERROR;
    }


    if(list->size < list->allocated_size) {
        list->elems[list->size++] = get_element_content(element);
        return OPERATION_SUCCESS;
    }
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

    void* tempPtr = NULL;

    tempPtr = realloc(list->elems, list->allocated_size * sizeof(void*));

    if(tempPtr == NULL) {
        destroy_list(list);
        set_return_code(element, OPERATION_ERROR);
    }

    return get_return_code(element);
}


Element get(List list, uint32_t index) {

    Element element;
    
    if(index >= list->size) {
        element = init_element(NULL, COMPONENT_NONE);
        set_return_code(element, OPERATION_ERROR);
        return element;
    }
    
    element = init_element(list->elems[index], OPERATION_SUCCESS);;

    return element;
}


uint32_t get_size(List list) {
    return list->size;
}


uint8_t insert_at(List list, uint32_t index, Element element) {

    if(index > list->size) {
        destroy_list(list);
        return OPERATION_ERROR;
    }

    if(push(list, element) != OPERATION_SUCCESS) {
        destroy_list(list);
        return OPERATION_ERROR;
    }

    // TODO
    return OPERATION_SUCCESS;
}


uint8_t del(List list, void* element) {

    bool found = false;
    uint8_t pos = 0;

    for(; !found && pos < list->size; pos++)
        if(list->elems[pos] == element) 
            found = true;

    if(!found) {
        destroy_list(list);
        return OPERATION_ERROR;
    }

    return del_at(list, pos);
}


uint8_t del_at(List list, uint32_t index) {

    if(index >= list->size) {
        destroy_list(list);
        return OPERATION_ERROR;
    }

    for(int pos = index; pos < (list->size)-1; pos++) {
        list->elems[pos] = list->elems[pos+1];
    }

    list->size--;

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

    void* tempPtr = realloc(list->elems, list->allocated_size);

    if(tempPtr == NULL) {
        destroy_list(list);
        return OPERATION_ERROR;
    }

    return OPERATION_SUCCESS;
}


uint8_t pop(List list) {
    return del_at(list, list->size);
}


void destroy_list(List list) {
    if(list->texture != NULL)
        SDL_DestroyTexture(list->texture);
    free(list->elems);
    free(list);
}