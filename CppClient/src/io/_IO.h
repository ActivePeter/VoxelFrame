#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class IO
{
private:
    /* data */
public:
    void processInput(GLFWwindow *window);
    void init();
};
