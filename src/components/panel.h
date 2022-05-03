#ifndef __PANEL_H__
#define __PANEL_H__

#include "list.h"
#include "label.h"

typedef struct s_panel* Panel;

// Returns OPERATION_ERROR if error, else OPERATION_SUCCESS
Panel init_panel();

uint8_t add_panel(Panel panel, Panel child_panel);

uint8_t add_list(Panel panel, List list);

uint8_t add_label(Panel panel, Label label);

void destroy_panel(Panel panel);

Component* get_components(const Panel panel);

uint32_t get_components_size(const Panel panel);

Panel* get_children_panels(const Panel panel);

uint32_t get_children_size(const Panel panel);

#endif