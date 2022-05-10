#ifndef __PANEL_H__
#define __PANEL_H__

#include "components_utils.h"
#include "label.h"
#include "list.h"
#include "textfield.h"

typedef struct s_panel* Panel;

// Returns OPERATION_ERROR if error, else OPERATION_SUCCESS
Panel init_panel();

uint8_t add_panel(Panel panel, Panel child_panel);

uint8_t add_component(Panel panel, Component component);

void set_panel_dimension(Panel panel, Dimension dimension);

void set_panel_position(Panel panel, Position position);

void destroy_panel(Panel panel);

Component* get_components(const Panel panel);

uint32_t get_components_size(const Panel panel);

Panel* get_children_panels(const Panel panel);

uint32_t get_children_size(const Panel panel);

#endif