#ifndef __COMPONENTS_RENDERING_H__
#define __COMPONENTS_RENDERING_H__

#include "window.h"
#include "label.h"
#include "list.h"
#include "textfield.h"


void render_label(void* window, Component component);

void render_list(void* window, Component component);

void render_button(void* window, Component component);

void render_image(void* window, Component component);

void render_textfield(void* window, Component component);

#endif