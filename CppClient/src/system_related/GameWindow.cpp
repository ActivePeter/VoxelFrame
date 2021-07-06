#include "GameWindow.h"
#include "vf_base.h"
// HWND handle;
bool GameWindow::createWindow()
{
    // this->window = glfwCreateWindow(
    //     this->windowW,
    //     this->windowH, WindowName, NULL, NULL);
    // // FindWindow();
    // // windowInfoModel.window = window;
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window " << std::endl;
    //     //销毁所有窗口
    //     glfwTerminate();
    //     return false;
    // }
    // //将该窗口作为当前线程的主上下文
    // glfwMakeContextCurrent(this->window);
    // //GLAD是管理OpenGL指针的，在调用任何OpenGL的函数之前需要初始化GLAD
    // if (!gladLoadGL())
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return false;
    // }

    //设置视口Viewport
    //前两个参数控制渲染窗口左下角的相对位置，第三和第四个参数控制渲染窗口的宽度和高度
    //OpenGL会在此窗口大小范围内进行坐标变换
    // glViewport(0, 0, 1080, 960);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error: %s\n"
                  << SDL_GetError() << '\n';
        return false;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    window = SDL_CreateWindow(
        WindowName,                                                         // title
        SDL_WINDOWPOS_CENTERED,                                             // x
        SDL_WINDOWPOS_CENTERED,                                             // y
        windowW, windowH,                                                   // width, height
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI // flags
    );
    GLContext = SDL_GL_CreateContext(window);
#ifdef __glad_h_
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
#endif

    //设置视口Viewport
    //前两个参数控制渲染窗口左下角的相对位置，第三和第四个参数控制渲染窗口的宽度和高度
    //OpenGL会在此窗口大小范围内进行坐标变换
    glViewport(0, 0, windowW, windowH);

    cursor.init(this);
    return true;
}
