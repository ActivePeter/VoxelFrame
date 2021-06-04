#include "Input.h"

#include "GLFW/glfw3.h"
#include "graph/_Graph.h"
// #include "Models/WindowInfoModel.h"
Input _g_IO_Input;

//处理输入
void process_input_callabck(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
//窗口大小变化时，重新设置视口
void framebuff_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    // WindowInfoModel &wim = WindowInfoModel::getInstance();
    // wim.Height = height;
    // wim.Width = width;
    _g_Graph.windowH = height;
    _g_Graph.windowW = width;
}

//在graph init之后调用
void Input::init()
{
    glfwSetFramebufferSizeCallback(_g_Graph.window, framebuff_size_callback);
    //处理输入
    // glfwSetCursorPosCallback(_g_Graph.window, mouse_callback);
    glfwSetKeyCallback(_g_Graph.window, process_input_callabck);
}
