#include "panel.h"

#define MIN_ALLOCATION 3
#define MORE_ALLOCATION 6
#define BIG_ALLOCATION 18

struct Panel {
    RenderingFunction rendering_function;
    DestroyFunction destroy_function;
    ComponentType component_type;
    Panel parent_panel;
    Dimension dimension;
    Position position;
    bool is_visible;
    bool is_rendered;
    bool is_pos_absolute;
    Window parent_window;
    Component* components;
    Panel* children_panels;
    uint32_t children_allocated;
    uint32_t children_size;
    uint32_t components_allocated;
    uint32_t components_size;
};

void set_parent_panel(Component component, Panel panel);

uint8_t render_panel(Component component);

void destroy_panel(Component component);

Panel init_panel() {

    Panel panel = malloc(sizeof(struct Panel));

    if(panel == NULL) {
        set_error("init_panel() : failed to allocate memory\n");
        return NULL;
    }

    panel->rendering_function = &render_panel;
    panel->destroy_function = &destroy_panel;

    panel->components = NULL;
    panel->dimension = init_dimension(0, 0);
    panel->position = init_position(0, 0);
    panel->parent_panel = NULL;
    panel->parent_window = NULL;
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


void set_parent_window(Panel panel, Window window) {
    panel->parent_window = window;
}


uint8_t add_panel(Panel panel, Panel child_panel) {

    if(panel->children_allocated == 0) {
        panel->children_panels = malloc(MIN_ALLOCATION * sizeof(Panel));
        panel->children_allocated = MIN_ALLOCATION;
        if(panel->children_panels == NULL)
            return set_error("add_panel() : failed to allocate memory\n");
    }

    if(panel->children_size >= panel->children_allocated) {

        Panel* tempPtr = NULL;

        if(panel->children_allocated < 2 * MIN_ALLOCATION)
            panel->children_allocated += MIN_ALLOCATION;            

        else
            panel->children_allocated += MORE_ALLOCATION;

        tempPtr = realloc(panel->children_panels, panel->children_allocated * sizeof(Panel));

        if(tempPtr == NULL)
            return set_error("add_panel() : failed to reallocate memory()\n");

        panel->children_panels = tempPtr;
    }

    child_panel->parent_panel = panel;

    panel->children_panels[panel->children_size++] = child_panel;

    return OPERATION_SUCCESS;
}


uint8_t add_component(Panel panel, Component component) {

    if(get_component_type(component) == COMPONENT_PANEL)
        return set_error("add_component() : failed to add component into panel because component type is a Panel, use add_panel(panel, other_panel) instead\n");

    if(panel->components_allocated == 0) {
        panel->components = malloc(MIN_ALLOCATION * sizeof(Component));
        panel->components_allocated = MIN_ALLOCATION;
        
        if(panel->components == NULL)
            return set_error("add_component() : failed to allocate memory\n");
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

        if(tempPtr == NULL)
            return set_error("add_component() : failed to reallocate memory\n");

        panel->components = tempPtr;
    }

    panel->components[panel->components_size++] = component;

    set_parent_panel(component, panel);

    return OPERATION_SUCCESS;
}


Window get_parent_window(Panel panel) {
    
    if(panel->parent_panel != NULL)
        return get_parent_window(panel->parent_panel);
    
    return panel->parent_window;
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

uint8_t render_panel(Component component) {

    //Panel panel = (Panel) component;

    return OPERATION_SUCCESS;
}

void destroy_panel(Component component) {

    Panel panel = (Panel) component;

    for(int i = 0; i < panel->components_size; i++) {
        destroy_component(panel->components[i]);
    }

    for(int i = 0; i < panel->children_size; i++) {
        destroy_panel((Component) panel->children_panels[i]);
    }

    free(panel->children_panels);
    free(panel->components);
    free(panel);
}