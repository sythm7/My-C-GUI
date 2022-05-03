#include "layout.h"

struct s_layout {
    void* content;
    uint8_t type;
};

Layout init_layout(void* content, uint8_t type) {

    Layout layout = malloc(sizeof(struct s_layout));

    layout->content = content;
    layout->type = type;

    return layout;
}

void* get_layout_content(Layout layout) {
    return layout->content;
}

uint8_t get_layout_type(Layout layout) {
    return layout->type;
}

void destroy_layout(Layout layout) {
    free(layout);
}