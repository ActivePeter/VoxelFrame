#include "glad/glad.h"
#include "_Input.h"

#include "GLFW/glfw3.h"
#include "graph/_Graph.h"
// #include "Models/WindowInfoModel.h"
// Input _g_Input_Input;
#include "app.h"

// #include "Input_sys.h"
//处理输入
void process_Input_callabck(GLFWwindow *window, int key, int scancode, int actInputn, int mods)
{
    if (key == GLFW_KEY_ESCAPE && actInputn == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    // auto &app = App::getInstance();
    // if (app.graphPtr && app.graphPtr->cameraPtr)
    // {
    //     auto &camera = *(App::getInstance().graphPtr->cameraPtr);
    //     if (actInputn == GLFW_PRESS || actInputn == GLFW_REPEAT)
    //     {
    //         switch (key)
    //         {
    //         case GLFW_KEY_W:
    //             camera.ProcessKeyboard(FORWARD, app.deltaTime);
    //             break;
    //         case GLFW_KEY_S:
    //             camera.ProcessKeyboard(BACKWARD, app.deltaTime);
    //             break;
    //         case GLFW_KEY_A:
    //             camera.ProcessKeyboard(LEFT, app.deltaTime);
    //             break;
    //         case GLFW_KEY_D:
    //             camera.ProcessKeyboard(RIGHT, app.deltaTime);
    //             break;
    //         default:
    //             break;
    //         }
    //         // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)

    //         // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)

    //         //     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)

    //         //         if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     }

    //     // App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
    // }
}
//窗口大小变化时，重新设置视口
void framebuff_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    // WindowInfoModel &wim = WindowInfoModel::getInstance();
    // wim.Height = height;
    // wim.Width = width;
    App::getInstance().graphPtr->gameWindow.windowH = height;
    App::getInstance().graphPtr->gameWindow.windowW = width;
    // _g_Graph.windowH = height;
    // _g_Graph.windowW = width;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    auto &input = *App::getInstance().inputPtr;
    // Input.cursorX = xpos;
    // Input.cursorY = ypos;

    auto &gameWindow = App::getInstance().graphPtr->gameWindow;

    int x = gameWindow.windowW / 2, y = gameWindow.windowH / 2;
    gameWindow.cursor.cursorX = xpos - x;
    gameWindow.cursor.cursorY = ypos - y;

    for (int i = 0; i < input.mouseMoveCallbacks.size(); i++)
    {
        input.mouseMoveCallbacks[i](xpos, ypos, xpos - x, ypos - y);
    }

    gameWindow.cursor.resetCursorPosIfLocked();
    // gameWindow.pos2Screen(x, y);

    // N_Input::setCursorPos(x, y);
    // camera 操作
    // {
    //     static bool firstMouse = true;
    //     static double lastX, lastY;
    //     if (firstMouse)
    //     {
    //         lastX = xpos;
    //         lastY = ypos;
    //         firstMouse = false;
    //     }

    //     float xoffset = xpos - lastX;
    //     float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    //     lastX = xpos;
    //     lastY = ypos;
    //     if (App::getInstance().graphPtr && App::getInstance().graphPtr->cameraPtr)
    //     {
    //         App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
    //     }
    // }
}
void Input::processInput(GLFWwindow *window)
{
    for (int i = 0; i < processInputCallbacks.size(); i++)
    {
        processInputCallbacks[i](*this);
    }
    // auto &app = App::getInstance();
    // auto &camera = *(App::getInstance().graphPtr->cameraPtr);
    // //     if (actInputn == GLFW_PRESS || actInputn == GLFW_REPEAT)
    // //     {
    // //         switch (key)
    // //         {
    // //         case GLFW_KEY_W:
    // //             camera.ProcessKeyboard(FORWARD, app.deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    // {
    //     camera.ProcessKeyboard(FORWARD, app.deltaTime);
    // }
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    // {
    //     camera.ProcessKeyboard(BACKWARD, app.deltaTime);
    // }
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    // {
    //     camera.ProcessKeyboard(LEFT, app.deltaTime);
    // }
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    // {
    //     camera.ProcessKeyboard(RIGHT, app.deltaTime);
    // }
    // glfwSetWindowShouldClose(window, true);
}
// camera

//在graph init之后调用
void Input::init()
{
    // auto &app = App::getInstance();
    auto window = App::getInstance().graphPtr->gameWindow.window;
    //窗口size 改变
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
    //处理输入
    // glfwSetCursorPosCallback(_g_Graph.window, mouse_callback);
    // glfwSetKeyCallback(app.graphPtr->window, process_Input_callabck);
    glfwSetCursorPosCallback(window, mouse_callback);
}

// int Input::getKey()
// {
//     return glfwGetKey(App::getInstance().graphPtr->window, GLFW_KEY_W);
// }
