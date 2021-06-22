#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Windows.h"

struct GameWindow
{
    int windowH = 800;
    int windowW = 1000;
    int windowX = 0;
    int windowY = 0;
    GLFWwindow *window;
    const char *WindowName = "VoxelFrame";
    bool createWindow();
    void pos2Screen(int &x, int &y);
};
