#include "GList.h"

#define MIN_LIST_SIZE 5
#define SHORT_LIST_SIZE 15
#define MEDIUM_LIST_SIZE 30
#define BIG_LIST_SIZE 100
#define VERY_BIG_LIST_SIZE 1000
#define GIANT_LIST_SIZE 100000

struct GList {
    GRenderingFunction rendering_function;
    GDestroyFunction destroy_function;
    GComponentType component_type;
    GPanel parent_panel;
    GDimension dimension;
    GPosition position;
    bool is_component_visible;
    bool is_component_rendered;
    bool is_pos_absolute;
    SDL_Texture* texture;
    SDL_Rect texture_dimension;
    GComponent* components;
    GComponentType type;
    uint32_t size;
    uint32_t allocated_size;
    uint8_t orientation;
    int padding;
};

uint8_t GListRender(void* component);
void GListDestroy(void* component);
uint8_t GListAddAlloc(GList list);
uint8_t GListDelAlloc(GList list);

GList GListInit(GColor color, uint8_t list_orientation, GComponentType type) {

    GDimension dimension = GDimensionInit(0, 0);

    GList list = malloc(sizeof(struct GList));

    if(list == NULL) {
        GError("GListInit() : failed to allocate memory\n");
        return NULL;
    }

    list->allocated_size = 0;

    list->components = malloc(list->allocated_size * sizeof(GComponent));

    if(list->components == NULL) {
        GError("GListInit() : failed to allocate memory\n");
        return NULL;
    }

    list->component_type = COMPONENT_LIST;
    list->rendering_function = &GListRender;
    list->destroy_function = &GListDestroy;
    list->is_component_rendered = false;
    list->is_component_visible = true;
    list->is_pos_absolute = false;

    list->size = 0;
    list->texture = NULL;
    list->dimension = dimension;

    list->orientation = list_orientation;
    list->padding = LIST_DEFAULT_PADDING;

    return list;
}


uint8_t GListAddComponent(GList list, void* component) {

    if(list->type != GComponentGetType(component))
        return GError("GListAddComponent() : failed to add component. The component doesn't have the same type as the list.\n");

    if(GListAddAlloc(list) == G_OPERATION_ERROR)
        return GError("GListAddComponent() : failed to reallocate memory\n");    

    list->components[list->size++] = component;

    return G_OPERATION_SUCCESS;
}


GComponent GListGetComponentAt(GList list, uint32_t index) {
    
    if(index >= list->size) {
        GError("GListGetComponentAt() : list size lower or equal to the given index. Can't get component\n");
        return NULL;
    }
    
    return (GComponent) list->components[index];
}


uint32_t GListGetSize(GList list) {
    return list->size;
}


uint8_t GListInsertComponentAt(GList list, uint32_t index, void* component) {

    if(index >= list->size)
        return GError("GListInsertComponentAt() : list size lower or equal to the given index. Can't insert component\n");

    if(GListAddAlloc(list) == G_OPERATION_ERROR)
        GError("GListInsertComponentAt() : failed to allocate memory\n");

    GComponent temp = list->components[index];
    list->components[index] = component;

    for(int i = index + 1; i < list->size + 1; i++) {
        GComponent temp1 = list->components[i];
        list->components[i] = temp;
        temp = temp1;
    }

    return G_OPERATION_SUCCESS;
}


uint8_t GListDelComponent(GList list, void* component) {

    bool found = false;
    uint8_t pos = 0;

    for(; !found && pos < list->size; pos++)
        if(list->components[pos] == component) 
            found = true;

    if(!found)
        return GError("GListDelComponent() : component not found in list. Can't delete component\n");

    uint8_t result = GListDelComponentAt(list, pos);

    if(result == G_OPERATION_ERROR)
        return GError("Call from GListDelComponent()\n");

    return G_OPERATION_SUCCESS;
}


uint8_t GListDelComponentAt(GList list, uint32_t index) {

    if(index >= list->size)
        return GError("GListDelComponentAt() : list size lower or equal to the given index. Can't delete component\n");


    for(int pos = index; pos < (list->size)-1; pos++) {
        list->components[pos] = list->components[pos+1];
    }

    list->size--;

    if(GListDelAlloc(list) == G_OPERATION_ERROR)
        return GError("GListDelComponentAt() : failed to reallocate memory\n");

    return G_OPERATION_SUCCESS;
}


uint8_t GListDelLastComponent(GList list) {

    uint8_t result = GListDelComponentAt(list, list->size);

    if(result == G_OPERATION_ERROR)
        return GError("Call from GListDelLastComponent()\n");

    return G_OPERATION_SUCCESS;
}


uint8_t GListAddAlloc(GList list) {

    if(list->size < list->allocated_size)
        return G_OPERATION_SUCCESS;

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

    GComponent* tempPtr = realloc(list->components, list->allocated_size * sizeof(GComponent));

    if(tempPtr == NULL)
        return G_OPERATION_ERROR;

    list->components = tempPtr;

    return G_OPERATION_SUCCESS;
}


uint8_t GListDelAlloc(GList list) {

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
        return G_OPERATION_SUCCESS;

    GComponent* tempPtr = realloc(list->components, list->allocated_size);

    if(tempPtr == NULL)
        return G_OPERATION_ERROR;

    list->components = tempPtr;

    return G_OPERATION_SUCCESS;
}

uint8_t GListRender(void* component) {

    // TODO
    return G_OPERATION_SUCCESS;
}

void GListDestroy(void* component) {

    GList list = (GList) component;

    if(list->texture != NULL)
        SDL_DestroyTexture(list->texture);

    for(int i = 0; i < list->size; i++) 
        GComponentDestroy(list->components[i]);

    free(list->components);
    free(list);
}