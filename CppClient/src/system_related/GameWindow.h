#pragma once
#include "system_related/_media_api.h"

#include "Cursor.h"

struct GameWindow
{
    int windowH = 800;
    int windowW = 1000;
    int windowX = 0;
    int windowY = 0;
    // bool cursorLocked = false;
    // GLFWwindow *window;
    SDL_Window *window;
    SDL_GLContext GLContext;
    const char *WindowName = "VoxelFrame";
    bool createWindow();
    void pos2Screen(int &x, int &y);
    Cursor cursor;
    // GameWindow();
    // void init();
};
