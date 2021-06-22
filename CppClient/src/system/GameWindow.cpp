#include "GameWindow.h"
#include "base.h"
HWND handle;
bool GameWindow::createWindow()
{
    this->window = glfwCreateWindow(
        this->windowW,
        this->windowH, WindowName, NULL, NULL);
    // FindWindow();
    // windowInfoModel.window = window;
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window " << std::endl;
        //销毁所有窗口
        glfwTerminate();
        return false;
    }
    handle = GetActiveWindow();
    RECT wr;
    GetWindowRect(handle, &wr);
    wr.top += 100;
    wr.bottom -= 100;
    wr.left += 100;
    wr.right -= 100;
    ClipCursor(&wr);
}

void GameWindow::pos2Screen(int &x, int &y)
{
    // LPPOINT p;
    POINT point;
    point.x = x;
    point.y = y;
    ClientToScreen(handle, &point);
    x = point.x;
    y = point.y;
}
