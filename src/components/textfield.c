#include "textfield.h"

struct s_textfield {
    TTF_Font* font;
    Color color;
    char* text;
    char* font_name;
    Position position;
    Dimension dimension;
    bool is_pos_absolute;
};

