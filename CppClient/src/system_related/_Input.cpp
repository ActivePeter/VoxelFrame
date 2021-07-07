#include "glad/glad.h"
#include "_Input.h"
#include "_media_api.h"
// #include "GLFW/glfw3.h"
#include "graph/_Graph.h"
// #include "Models/WindowInfoModel.h"
// Input _g_Input_Input;
#include "app.h"

// #include "Input_sys.h"
//处理输入
// void process_Input_callabck(GLFWwindow *window, int key, int scancode, int actInputn, int mods)
// {
//     if (key == GLFW_KEY_ESCAPE && actInputn == GLFW_PRESS)
//     {
//         glfwSetWindowShouldClose(window, true);
//     }
//     // auto &app = App::getInstance();
//     // if (app.graphPtr && app.graphPtr->cameraPtr)
//     // {
//     //     auto &camera = *(App::getInstance().graphPtr->cameraPtr);
//     //     if (actInputn == GLFW_PRESS || actInputn == GLFW_REPEAT)
//     //     {
//     //         switch (key)
//     //         {
//     //         case GLFW_KEY_W:
//     //             camera.ProcessKeyboard(FORWARD, app.deltaTime);
//     //             break;
//     //         case GLFW_KEY_S:
//     //             camera.ProcessKeyboard(BACKWARD, app.deltaTime);
//     //             break;
//     //         case GLFW_KEY_A:
//     //             camera.ProcessKeyboard(LEFT, app.deltaTime);
//     //             break;
//     //         case GLFW_KEY_D:
//     //             camera.ProcessKeyboard(RIGHT, app.deltaTime);
//     //             break;
//     //         default:
//     //             break;
//     //         }
//     //         // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)

//     //         // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)

//     //         //     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)

//     //         //         if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//     //     }

//     //     // App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
//     // }
// }
// //窗口大小变化时，重新设置视口
// void framebuff_size_callback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
//     // WindowInfoModel &wim = WindowInfoModel::getInstance();
//     // wim.Height = height;
//     // wim.Width = width;
//     App::getInstance().graphPtr->gameWindow.windowH = height;
//     App::getInstance().graphPtr->gameWindow.windowW = width;
//     // _g_Graph.windowH = height;
//     // _g_Graph.windowW = width;
// }

// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     auto &input = *App::getInstance().inputPtr;
//     // Input.cursorX = xpos;
//     // Input.cursorY = ypos;

//     auto &gameWindow = App::getInstance().graphPtr->gameWindow;

//     int x = gameWindow.windowW / 2, y = gameWindow.windowH / 2;
//     gameWindow.cursor.cursorX = xpos - x;
//     gameWindow.cursor.cursorY = ypos - y;

//     for (int i = 0; i < input.mouseMoveCallbacks.size(); i++)
//     {
//         input.mouseMoveCallbacks[i](xpos, ypos, xpos - x, ypos - y);
//     }

//     gameWindow.cursor.resetCursorPosIfLocked();
//     // gameWindow.pos2Screen(x, y);

//     // N_Input::setCursorPos(x, y);
//     // camera 操作
//     // {
//     //     static bool firstMouse = true;
//     //     static double lastX, lastY;
//     //     if (firstMouse)
//     //     {
//     //         lastX = xpos;
//     //         lastY = ypos;
//     //         firstMouse = false;
//     //     }

//     //     float xoffset = xpos - lastX;
//     //     float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

//     //     lastX = xpos;
//     //     lastY = ypos;
//     //     if (App::getInstance().graphPtr && App::getInstance().graphPtr->cameraPtr)
//     //     {
//     //         App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
//     //     }
//     // }
// }
// void mouseBtn_callback(GLFWwindow *, int btn, int action, int mods)
// {
//     auto &input = *App::getInstance().inputPtr;
//     for (auto iter = input.mouseBtnCallbacks.begin(); iter != input.mouseBtnCallbacks.end(); iter++)
//     {
//         (*iter)(btn, action);
//     }
// }

void Input::processInput()
{
    auto &gameWindow = App::getInstance().graphPtr->gameWindow;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // printf("poll event\r\n");
        if (SDL_QUIT == event.type)
        {
            // quit = true;
        }
        if (event.type == SDL_KEYDOWN)
        {
            // printf("hhhh");
            // std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            static int oldX = 0;
            static int oldY = 0;
            if (gameWindow.cursor.getLocked())
            {
                for (auto *i : mouseMovePublisher.listeners)
                {
                    i->MouseMoveListenerCallback(gameWindow.windowW / 2, gameWindow.windowH / 2, event.motion.x - gameWindow.windowW / 2, event.motion.y - gameWindow.windowH / 2);
                }
            }
            else
            {
                for (auto *i : mouseMovePublisher.listeners)
                {
                    i->MouseMoveListenerCallback(event.motion.x, event.motion.y, event.motion.x - oldX, event.motion.y - oldY);
                }
            }

            oldX = event.motion.x;
            oldY = event.motion.y;
        }
    }
    gameWindow.cursor.resetCursorPosIfLocked();

    for (int i = 0; i < processInputCallbacks.size(); i++)
    {
        processInputCallbacks[i](*this);
    }
}
// camera

//在graph init之后调用
void Input::init()
{
    // auto &app = App::getInstance();
    auto window = App::getInstance().graphPtr->gameWindow.window;
    //窗口size 改变
    // glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
    // //处理输入
    // // glfwSetCursorPosCallback(_g_Graph.window, mouse_callback);
    // // glfwSetKeyCallback(app.graphPtr->window, process_Input_callabck);
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetMouseButtonCallback(window, mouseBtn_callback);
}

Input_KeyState Input::getKey(int M_KeyCode)
{
    // SDLK_a;
    // printf("keycode %d \r\n", M_KeyCode);
    // SDLK_LEFT
    static int len;
    static const Uint8 *keyStates = 0;
    if (!keyStates)
    {
        keyStates = SDL_GetKeyboardState(&len);
    }
    // auto keyStates =
    if (M_KeyCode >= len)
    {
        return Input_KeyState::E_KeyUp;
    }
    // for (int i = 0; i < len; i++)
    // {
    //     printf("%d", keyStates[M_KeyCode]);
    // }
    // printf("\r\n");
    return (Input_KeyState)keyStates[M_KeyCode]; //(Input_KeyState)glfwGetKey(App::getInstance().graphPtr->gameWindow.window, M_KeyCode);
}

// int Input::getKey()
// {
//     return glfwGetKey(App::getInstance().graphPtr->window, GLFW_KEY_W);
// }
