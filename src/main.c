#include <stdio.h>
#include <unistd.h>
#include "windows/LoginWindow.h"
#include "windows/AppWindow.h"
#include <stdlib.h>
#include <libgen.h>

#define MAX_PATH 256

char G_Program_Path[MAX_PATH];

void init_prog_path();


int main(int argc, char* argv[]) {

    init_prog_path();

    GWindow login_window = create_login_window();

    if(GWindowDisplay(login_window) == G_OPERATION_ERROR) {
        GWindowDestroy(login_window);
        return EXIT_FAILURE;
    }
    
    // -------------
    // Lines of code
    //--------------

    GWindowDestroy(login_window);
    
    return EXIT_SUCCESS;
}



void init_prog_path() {

    #if defined(_WIN32)
    strcpy(G_Program_Path, dirname(_pgmptr));
    #elif defined(__linux__)
    pid_t pid = getpid();

    char path[256];
    char path2[256];
    snprintf(path, sizeof(path), "/proc/%d/exe", pid);
    readlink(path, path2, 256);
    strcpy(G_Program_Path, dirname(path2));
    printf("%s\n", G_Program_Path);
    #endif

    chdir(G_Program_Path);
}