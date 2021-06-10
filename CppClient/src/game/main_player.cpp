#include "main_player.h"
#include "App.h"
#include "io.h"

namespace main_plaer_about
{
    void mouse_callback(double xpos, double ypos)
    {
        // camera 操作
        static bool firstMouse = true;
        static double lastX, lastY;
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        auto gamePtr = App::getInstance().gamePtr;
        if (gamePtr)
        {
            gamePtr->mainPlayer->ProcessMouseMovement(xoffset, yoffset);
        }
        // if (App::getInstance().graphPtr && App::getInstance().graphPtr->cameraPtr)
        // {
        //     App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
        // }
    }
    void processInput(IO &io)
    {
        // for (int i = 0; i < processInputCallbacks.size(); i++)
        // {
        //     processInputCallbacks[i](*this);
        // }
        // auto &app = App::getInstance();
        // auto &camera = *(App::getInstance().graphPtr->cameraPtr);
        // //     if (action == GLFW_PRESS || action == GLFW_REPEAT)
        // //     {
        // //         switch (key)
        // //         {
        // //         case GLFW_KEY_W:
        // //             camera.ProcessKeyboard(FORWARD, app.deltaTime);

        auto &app = App::getInstance();
        auto window = App::getInstance().graphPtr->window;
        if (app.gamePtr)
        {
            auto player = *app.gamePtr->mainPlayer;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                player.ProcessKeyboard(MainPlayer::FORWARD, app.deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                player.ProcessKeyboard(MainPlayer::BACKWARD, app.deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                player.ProcessKeyboard(MainPlayer::LEFT, app.deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                player.ProcessKeyboard(MainPlayer::RIGHT, app.deltaTime);
            }
        }

        // glfwSetWindowShouldClose(window, true);
    }
}

MainPlayer::MainPlayer()
{
    cameraPtr = App::getInstance().getInstance().graphPtr->cameraPtr;
    auto &io = *App::getInstance().ioPtr;
    io.registerMouseMove();
}
