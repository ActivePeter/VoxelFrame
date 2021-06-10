#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "base.h"

class IO;
#pragma once

class IO
{
public:
    using ProcessInputFunc = void (*)(IO &io);
    using MouseMoveFunc = void (*)(double xpos, double ypos);

private:
    /* data */
    // vector<>
public:
    std::vector<MouseMoveFunc> mouseMoveCallbacks;
    std::vector<ProcessInputFunc> processInputCallbacks;
    inline int getKey();
    void processInput(GLFWwindow *window);
    void init();
    /**
     * 注册鼠标移动回调。
     * 注意没有重复性检查，所以要确保每个函数只注册一次
    */
    void registerMouseMove(MouseMoveFunc f)
    {
        mouseMoveCallbacks.push_back(f);
    }
    void registerProcessInput(ProcessInputFunc f)
    {
        processInputCallbacks.push_back(f);
    }
};
