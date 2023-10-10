#include "GImage.h"

struct GImage {
    // Start GComponent
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
    SDL_Rect src_dimension;
    GEventFunction* event_list;
    int event_list_size;
    int event_list_allocated;
    // End GComponent

    char* image_path;
    bool is_pressed;
};


uint8_t GImageRender(void* component);
void GImageDestroy(void* component);


GImage GImageInit(const char* image_path, bool is_clickable) {
    // GImage image = malloc(sizeof(struct GImage));
    // image->rendering_function = &GImageRender;
    // image->destroy_function = &GImageDestroy;
    // image->component_type = COMPONENT_IMAGE;
    // image->parent_panel = NULL;
    // image->position = GPositionInit(0, 0);
    // image->dimension = GDimensionInit(-1, -1);
    // image->is_component_visible = true;
    // image->is_component_rendered = false;
    // image->is_pos_absolute = false;

    GComponent component = GComponentInit(&GImageRender, &GImageDestroy, COMPONENT_IMAGE);

    if(component == NULL)
        return NULL;

    GImage image = realloc(component, sizeof(struct GImage));

    if(image == NULL) {
        GError("GImageInit() : failed to allocate memory\n");
        return NULL;
    }
    
    image->is_pressed = false;
    //image->image_path = image_path;

    return image;
}


uint8_t GImageRender(void* component) {
    return G_OPERATION_SUCCESS;
}


void GImageDestroy(void* component) {
    
}