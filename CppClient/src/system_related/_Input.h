// #include "glad/glad.h"
// #include "GLFW/glfw3.h"
#include "base/vf_base.h"
#include "_Input_Map.h"
#include "MouseMoveEvent.h"
// #include "Input_sys.h"
/**
 * 
 * handle input
 * 
*/
class Input;

#pragma once
enum class Input_KeyState {
    KeyDown = 1,
    KeyUp = 0,
};

class Input {
public:
    // using ProcessInputFunc = void (*)(Input &Input);
    using MouseMoveFunc = void (*)(double xpos, double ypos, double dx, double dy);

private:
    /* data */
    // vector<>
public:
    VF::Event::MouseMove_EventPublisher mouseMovePublisher;
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
    void registerMouseMove(MouseMoveFunc f) {
        mouseMoveCallbacks.push_back(f);
    }

    void registerProcessInput(void (*f)(Input &Input)) {
        processInputCallbacks.push_back(f);
    }

    void registerMouseClick(void (*hhh)(int btn, int action)) {
        mouseBtnCallbacks.emplace_back(hhh);
    }
};
