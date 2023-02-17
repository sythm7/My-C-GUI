#include "GPanel.h"
#include <stdarg.h>

#define MIN_ALLOCATION 3
#define MORE_ALLOCATION 6
#define BIG_ALLOCATION 18

#define GPANEL_DEFAULT_COLOR GColorInit(0, 0, 0, 0)

struct GPanel {
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
    GWindow parent_window;
    GComponent* components;
    GPanel* children_panels;
    uint32_t children_allocated;
    uint32_t children_size;
    uint32_t components_allocated;
    uint32_t components_size;
    GColor color;
    bool left_border;
    bool right_border;
    bool top_border;
    bool bottom_border;
    uint8_t border_size;
};


void GComponentSetParentPanel(void* component, GPanel panel);
uint8_t GPanelRender(void* component);
uint8_t GPanelRenderBorder(GPanel panel);
void GPanelGetComponentName(void* component, char component_name[]);
SDL_Renderer* GWindowGetSDL_Renderer(GWindow window);
void GComponentAdaptDimension(void* component);
void GComponentSetTextureDimension(void* component, SDL_Rect dimension);
SDL_Rect GComponentGetTextureDimension(void* component);


GPanel GPanelInit() {

    GPanel panel = malloc(sizeof(struct GPanel));

    if(panel == NULL) {
        GError("GPanelInit() : failed to allocate memory\n");
        return NULL;
    }

    panel->rendering_function = &GPanelRender;
    panel->destroy_function = &GPanelDestroy;
    panel->components = NULL;
    panel->dimension = GDimensionInit(0, 0);
    panel->position = GPositionInit(0, 0);
    panel->parent_panel = NULL;
    panel->parent_window = NULL;
    panel->components_allocated = 0;
    panel->components_size = 0;
    panel->children_size = 0;
    panel->children_allocated = 0;
    panel->children_panels = NULL;
    panel->color = GPANEL_DEFAULT_COLOR;
    panel->texture = NULL;
    GPanelSetBorder(panel, 0, false, false, false, false);

    return panel;
}


void GPanelSetColor(GPanel panel, GColor color) {
    panel->color = color;
}


void GPanelSetBorder(GPanel panel, uint8_t size, bool top, bool bottom, bool left, bool right) {
    panel->border_size = size;
    panel->top_border = top;
    panel->bottom_border = bottom;
    panel->left_border = left;
    panel->right_border = right;
}


void GPanelSetParentWindow(GPanel panel, GWindow window) {
    panel->parent_window = window;
}


uint8_t GPanelAddChild(GPanel panel, GPanel child_panel) {

    if(panel->children_allocated == 0) {
        panel->children_panels = malloc(MIN_ALLOCATION * sizeof(GPanel));
        panel->children_allocated = MIN_ALLOCATION;
        if(panel->children_panels == NULL)
            return GError("GPanelAddChild() : failed to allocate memory\n");
    }

    if(panel->children_size >= panel->children_allocated) {

        GPanel* tempPtr = NULL;

        if(panel->children_allocated < 2 * MIN_ALLOCATION)
            panel->children_allocated += MIN_ALLOCATION;            

        else
            panel->children_allocated += MORE_ALLOCATION;

        tempPtr = realloc(panel->children_panels, panel->children_allocated * sizeof(GPanel));

        if(tempPtr == NULL)
            return GError("GPanelAddChild() : failed to reallocate memory()\n");

        panel->children_panels = tempPtr;
    }

    child_panel->parent_panel = panel;

    panel->children_panels[panel->children_size++] = child_panel;

    return G_OPERATION_SUCCESS;
}


uint8_t GPanelAddComponent(GPanel panel, void* component) {

    if(GComponentGetType(component) == COMPONENT_PANEL)
        return GError("GPanelAddComponent() : failed to add component into panel because component type is a GPanel, use GPanelAddChild(panel, other_panel) instead\n");

    if(panel->components_allocated == 0) {
        panel->components = malloc(MIN_ALLOCATION * sizeof(GComponent));
        panel->components_allocated = MIN_ALLOCATION;
        
        if(panel->components == NULL)
            return GError("GPanelAddComponent() : failed to allocate memory\n");
    }

    if(panel->components_size >= panel->components_allocated) {

        GComponent* tempPtr = NULL;

        if(panel->components_allocated < 2 * MIN_ALLOCATION)
            panel->components_allocated += MIN_ALLOCATION;
        else if(panel->components_allocated < 4 * MORE_ALLOCATION)
            panel->components_allocated += MORE_ALLOCATION;
        else
            panel->components_allocated += BIG_ALLOCATION;

        tempPtr = realloc(panel->components, panel->components_allocated * sizeof(GComponent));

        if(tempPtr == NULL)
            return GError("GPanelAddComponent() : failed to reallocate memory\n");

        panel->components = tempPtr;
    }

    panel->components[panel->components_size++] = (GComponent) component;

    GComponentSetParentPanel(component, panel);

    return G_OPERATION_SUCCESS;
}


GWindow GPanelGetWindow(const GPanel panel) {
        if(panel->parent_panel != NULL)
            return GPanelGetWindow(panel->parent_panel);
    
    return panel->parent_window;
}


GComponent* GPanelGetComponentList(const GPanel panel) {
    return panel->components;
}


uint32_t GPanelGetComponentListSize(const GPanel panel) {
    return panel->components_size;
}


GPanel* GPanelGetChildList(const GPanel panel) {
    return panel->children_panels;
}


uint32_t GPanelGetChildListSize(const GPanel panel) {
    return panel->children_size;
}


void GPanelGetComponentName(void* component, char component_name[]) {

    switch(GComponentGetType(component)) {
        case COMPONENT_BUTTON :
            strcpy(component_name, "BUTTON");
            break;
        case COMPONENT_IMAGE :
            strcpy(component_name, "IMAGE");
            break;
        case COMPONENT_LABEL :
            strcpy(component_name, "LABEL");
            break;
        case COMPONENT_LIST :
            strcpy(component_name, "LIST");
            break;
        case COMPONENT_TEXTFIELD :
            strcpy(component_name, "TEXTFIELD");
            break;
        default :
            strcpy(component_name, "UNKNOWN_COMPONENT");
            break;
    }
}


uint8_t GPanelRenderBackground(GPanel panel) {

    SDL_Renderer* renderer = GWindowGetSDL_Renderer(GPanelGetWindow(panel));

    if(panel->texture == NULL) {
        panel->texture = SDL_CreateTexture(GWindowGetSDL_Renderer(GPanelGetWindow(panel)), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, panel->dimension.width, panel->dimension.height);
        
        if(panel->texture == NULL) {
            return GError("GPanelInit() : failed to create texture\n");
        }
        SDL_SetTextureBlendMode(panel->texture, SDL_BLENDMODE_BLEND);
    }

    if(SDL_SetRenderTarget(renderer, panel->texture) != 0)
        return GError(SDL_GetError());;

    if(SDL_SetRenderDrawColor(renderer, panel->color.r, panel->color.g, panel->color.b, panel->color.a) != 0)
        return GError(SDL_GetError());

    if(SDL_RenderClear(renderer) != 0)
        return GError(SDL_GetError());

    if(SDL_SetRenderTarget(renderer, NULL) != 0)
        return GError(SDL_GetError());

    if(SDL_RenderCopy(renderer, panel->texture, NULL, &panel->texture_dimension) != 0)
        return GError(SDL_GetError());

    return G_OPERATION_SUCCESS;
}


uint8_t GPanelRenderBorder(GPanel panel) {

    if(panel->border_size > 0) {
        
        if(panel->top_border) {

        }
        if(panel->bottom_border) {

        }
        if(panel->left_border) {

        }
        if(panel->right_border) {

        }

    }


    return G_OPERATION_SUCCESS;
}


uint8_t GPanelRender(void* component) {

    GPanel panel = (GPanel) component;

    GComponent* panel_components = GPanelGetComponentList(panel);
    uint32_t panel_components_size = GPanelGetComponentListSize(panel);

    char component_name[15];

    if(GPanelRenderBackground(panel) == G_OPERATION_ERROR)
        return G_OPERATION_ERROR;

    for(int i = 0; i < panel_components_size; i++) {
        GComponent panel_component = panel_components[i];

        GRenderingFunction render_component = GComponentGetRenderingFunction(panel_component);

        GComponentAdaptDimension(panel_component);

        if(render_component != NULL)
            render_component(panel_component);
        else {
            GPanelGetComponentName(panel_component, component_name);
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "NULL rendering function for component %s\n", component_name);
        }
    }

    for(int i = 0; i < panel->children_size; i++) {

        GPanel child_panel = panel->children_panels[i];

        GRenderingFunction render_panel = GComponentGetRenderingFunction(child_panel);

        GComponentAdaptDimension(child_panel);

        render_panel(child_panel);
    }

    return G_OPERATION_SUCCESS;
}


void GPanelDestroy(void* component) {

    GPanel panel = (GPanel) component;

    for(int i = 0; i < panel->components_size; i++) {
        GComponentDestroy(panel->components[i]);
    }

    for(int i = 0; i < panel->children_size; i++) {
        GPanelDestroy(panel->children_panels[i]);
    }

    if(panel->texture != NULL)
        SDL_DestroyTexture(panel->texture);

    free(panel->children_panels);
    free(panel->components);
    free(panel);
}