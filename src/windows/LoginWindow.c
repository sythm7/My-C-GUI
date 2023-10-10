#include "LoginWindow.h"
#include <stdio.h>

char* real_username = "Sythm";
char* real_password = "bienvenue";

GTextfield username_textfield = NULL;
GTextfield password_textfield = NULL;

int button_click_event(void* data, SDL_Event* event) {

    GButton button = (GButton) data;

    GPosition cursor_position;

    SDL_GetMouseState(&cursor_position.x, &cursor_position.y);

    if(GComponentLeftClicked(event, button)) {
        
        // verify_credentials();
        
        // char* username = GTextfieldGetText(username_textfield);
        // char* password = GTextfieldGetText(password_textfield);

        // if(strcmp(username, real_username) != 0 || strcmp(password, real_password) != 0) {
        //     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Invalid credentials !", "The username or password is incorrect", GWindowGetSDL_Window(GComponentGetWindow((GComponent) button)));
        //     return 0;
        // }

        //GWindowClose(GComponentGetWindow(button));

        GWindow app_window = create_app_window();

        GWindowDisplay(app_window);
    }

    return 0;
}


GWindow create_login_window() {

    GDimension dimension = GDimensionInit(DEFAULT_LOGIN_WIDTH, DEFAULT_LOGIN_HEIGHT);

    GColor background_color = GColorInit(33, 37, 43, 255);
    
    GWindow window = GWindowInit(DEFAULT_TITLE, background_color, SDL_WINDOW_OPENGL);

    GPanel panel = GPanelInit();

    // Labels initialisation
    GLabel welcome_label = GLabelInit(DEFAULT_FONT, 40);
    GLabel username_label = GLabelInit(DEFAULT_FONT, 30);
    GLabel password_label = GLabelInit(DEFAULT_FONT, 30);

    // Textfields initialisation
    username_textfield = GTextfieldInit(ARIAL_FONT, 15, GDimensionInit(150, 30));
    password_textfield = GTextfieldInit(ARIAL_FONT, 15, GDimensionInit(150, 30));

    if(username_textfield == NULL || password_textfield == NULL)
        return NULL;

    // GButton initialisation
    GButton ok_button = GButtonInit();

    GLabelSetText(welcome_label, "Welcome to MyApp !");

    GComponentSetPosition(welcome_label, GPositionInit(55, 75));

    GLabelSetText(username_label, "Username :");

    GComponentSetPosition(username_label, GPositionInit(135, 190));

    GLabelSetText(password_label, "Password :");

    GComponentSetPosition(password_label, GPositionInit(135, 300));

    GComponentSetPosition(username_textfield, GPositionInit(125, 240));

    GComponentSetPosition(password_textfield, GPositionInit(125, 340));

    GButtonSetText(ok_button, DEFAULT_FONT, 30, "Ok");

    GButtonSetColor(ok_button, GColorInit(47, 53, 61, 255));
    
    GComponentSetPosition(ok_button, GPositionInit(175, 430));

    GComponentSetDimension(panel, dimension);

    GWindowSetPanel(window, panel);

    GPanelAddComponent(panel, welcome_label);

    GPanelAddComponent(panel, username_label);

    GPanelAddComponent(panel, password_label);

    GPanelAddComponent(panel, username_textfield);

    GPanelAddComponent(panel, password_textfield);

    GPanelAddComponent(panel, ok_button);

    GWindowSetDimension(window, dimension);

    GWindowCenterPosition(window);

    GComponentAddListener(&button_click_event, ok_button);

    return window;
}