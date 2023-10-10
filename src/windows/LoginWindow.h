#ifndef __LOGIN_WINDOW_H__
#define __LOGIN_WINDOW_H__

#include "../engine/GWindow.h"
#include "AppWindow.h"

#define DEFAULT_LOGIN_WIDTH 400
#define DEFAULT_LOGIN_HEIGHT 550
#define DEFAULT_TITLE "MyApp"
#define DEFAULT_FONT "../font/OpticalFiberBold.ttf"
#define ARIAL_FONT "../font/Arial.ttf"

GWindow create_login_window();

#endif