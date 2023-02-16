#include "AppWindow.h"
#include <stdio.h>

#define BACKGROUND_COLOR GColorInit(33, 37, 43, 0)

void init_main_panel();
void init_left_panel();
void init_right_panel();
void init_left_top_panel();
void init_left_mid_panel();
void init_left_bottom_panel();

GPanel panel = NULL;
GPanel left_panel = NULL;
GPanel right_panel = NULL;
GPanel left_top_panel = NULL;
GPanel left_mid_panel = NULL;
GPanel left_bottom_panel = NULL;

GWindow window = NULL;

GWindow create_app_window() {
    
    GColor background_color = BACKGROUND_COLOR;
    window = GWindowInit(DEFAULT_TITLE, background_color, SDL_WINDOW_RESIZABLE);
    GWindowSetDimension(window, GDimensionInit(DEFAULT_APP_WIDTH, DEFAULT_APP_HEIGHT));
    GWindowCenterPosition(window);

    init_main_panel();
    init_left_panel();
    init_right_panel();
    init_left_top_panel();

    return window;
}


void init_main_panel() {

    panel = GPanelInit();

    GComponentSetDimension(panel, GDimensionInit(DEFAULT_APP_WIDTH, DEFAULT_APP_HEIGHT));

    GWindowSetPanel(window, panel);
}


void init_left_panel() {

    left_panel = GPanelInit();

    GComponentSetDimension(left_panel, GDimensionInit(175, 720));

    GPanelSetColor(left_panel, GColorInit(255, 0, 0, 100));

    GPanelAddChild(panel, left_panel);
}


void init_right_panel() {

    right_panel = GPanelInit();

    GComponentSetDimension(right_panel, GDimensionInit(1105, 720));

    GComponentSetPosition(right_panel, GPositionInit(175, 0));

    GPanelSetColor(right_panel, GColorInit(0, 0, 255, 100));

    GPanelAddChild(panel, right_panel);

}

void init_left_top_panel() {

    left_top_panel = GPanelInit();

    GLabel label = GLabelInit(DEFAULT_FONT, 35);

    GLabelSetText(label, "Ceci est un test ...");

    GPanelAddComponent(left_top_panel, label);

    GComponentSetDimension(left_top_panel, GDimensionInit(225, 40));

    GPanelSetColor(left_top_panel, GColorInit(0, 255, 0, 100));

    GPanelAddChild(left_panel, left_top_panel);
}


void init_left_mid_panel() {

}


void init_left_bottom_panel() {

}