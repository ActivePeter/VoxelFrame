#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "base.h"
// #include "Input_sys.h"
/**
 * 
 * handle input
 * 
*/
class Input;
#pragma once

class Input
{
public:
    using ProcessInputFunc = void (*)(Input &Input);
    using MouseMoveFunc = void (*)(double xpos, double ypos, double dx, double dy);

private:
    /* data */
    // vector<>
public:
    std::vector<MouseMoveFunc> mouseMoveCallbacks;
    std::vector<ProcessInputFunc> processInputCallbacks;
    // inline int getKey();
    void processInput(GLFWwindow *window);
    void init();
    //锁定光标
    bool cursorLocked = true;
    float cursorX = 0;
    float cursorY = 0;
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
