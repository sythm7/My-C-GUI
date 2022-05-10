#include "panel.h"

#define MIN_ALLOCATION 3
#define MORE_ALLOCATION 6
#define BIG_ALLOCATION 18

struct s_panel {
    void* layout;
    Component* components;
    Dimension dimension;
    Position position;
    Panel* children_panels;
    Panel parent_panel;
    uint32_t children_allocated;
    uint32_t children_size;
    uint32_t components_allocated;
    uint32_t components_size;
};

Panel init_panel() {

    Panel panel = malloc(sizeof(struct s_panel));

    if(panel == NULL)
        return NULL;

    panel->layout = NULL;
    panel->components = NULL;
    panel->dimension = init_dimension(0, 0);
    panel->position = init_position(0, 0);

    panel->components_allocated = 0;
    panel->components_size = 0;
    panel->children_size = 0;
    panel->children_allocated = 0;
    panel->children_panels = NULL;

    return panel;
}


void set_panel_dimension(Panel panel, Dimension dimension) {

    panel->dimension = dimension;
}


void set_panel_position(Panel panel, Position position) {

    panel->position = position;
}


uint8_t add_panel(Panel panel, Panel child_panel) {

    if(panel->children_allocated == 0) {
        panel->children_panels = malloc(MIN_ALLOCATION * sizeof(Panel));
        panel->children_allocated = MIN_ALLOCATION;
        if(panel->children_panels == NULL)
            return OPERATION_ERROR;
    }

    if(panel->children_size >= panel->children_allocated) {

        Panel* tempPtr = NULL;

        if(panel->children_allocated < 2 * MIN_ALLOCATION) {
            tempPtr = realloc(panel->children_panels, (panel->children_allocated + MIN_ALLOCATION) * sizeof(Panel));
            panel->children_allocated += MIN_ALLOCATION;
        }

        else {
            tempPtr = realloc(panel->children_panels, MORE_ALLOCATION * sizeof(Panel));
            panel->children_allocated += MORE_ALLOCATION;
        }

        if(tempPtr == NULL) {
            destroy_panel(panel);
            return OPERATION_ERROR;
        }
    }

    child_panel->parent_panel = panel;
    panel->children_panels[panel->children_size++] = child_panel;

    return OPERATION_SUCCESS;
}


uint8_t add_component(Panel panel, Component component) {

    if(panel->components_allocated == 0) {
        panel->components = malloc(MIN_ALLOCATION * sizeof(Component));
        panel->components_allocated = MIN_ALLOCATION;
        
        if(panel->components == NULL)
            return OPERATION_ERROR;
    }

    if(panel->components_size >= panel->components_allocated) {

        Component* tempPtr = NULL;

        if(panel->components_allocated < 2 * MIN_ALLOCATION)
            panel->components_allocated += MIN_ALLOCATION;
        else if(panel->components_allocated < 4 * MORE_ALLOCATION)
            panel->components_allocated += MORE_ALLOCATION;
        else
            panel->components_allocated += BIG_ALLOCATION;

        tempPtr = realloc(panel->components, panel->components_allocated * sizeof(Component));

        if(tempPtr == NULL) {
            destroy_panel(panel);
            return OPERATION_ERROR;
        }
    }

    panel->components[panel->components_size++] = component;

    return OPERATION_SUCCESS;
}

Component* get_components(const Panel panel) {
    return panel->components;
}

uint32_t get_components_size(const Panel panel) {
    return panel->components_size;
}

Panel* get_children_panels(const Panel panel) {
    return panel->children_panels;
}

uint32_t get_children_size(const Panel panel) {
    return panel->children_size;
}

void destroy_panel(Panel panel) {
    free(panel->children_panels);
    free(panel->components);
    free(panel);
}