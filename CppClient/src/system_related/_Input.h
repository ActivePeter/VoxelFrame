// #include "glad/glad.h"
// #include "GLFW/glfw3.h"
#include "base.h"
#include "_Input_Map.h"
// #include "Input_sys.h"
/**
 * 
 * handle input
 * 
*/
class Input;
#pragma once
enum Input_KeyState
{
    E_KeyDown = 1,
    E_KeyUp = 0,
};
class Input
{
public:
    // using ProcessInputFunc = void (*)(Input &Input);
    using MouseMoveFunc = void (*)(double xpos, double ypos, double dx, double dy);

private:
    /* data */
    // vector<>
public:
    std::vector<MouseMoveFunc> mouseMoveCallbacks;
    std::vector<void (*)(Input &Input)> processInputCallbacks;
    std::deque<void (*)(int btn, int action)> mouseBtnCallbacks;
    // inline int getKey();
    void processInput();
    void init();
    Input_KeyState getKey(int M_KeyCode);
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
    void registerProcessInput(void (*f)(Input &Input))
    {
        processInputCallbacks.push_back(f);
    }
    void registerMouseClick(void (*hhh)(int btn, int action))
    {
        mouseBtnCallbacks.emplace_back(hhh);
    }
};
