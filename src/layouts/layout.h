#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include <stdint.h>
#include <stdlib.h>

typedef struct s_layout* Layout;

Layout init_layout(void* layout, uint8_t type);

void* get_layout_content(Layout layout);

uint8_t get_layout_type(Layout layout);

void destroy_layout(Layout layout);

#endif
