// #include "DrawSys.h"
// #include "glad/glad.h"

#include "_Graph.h"

#include "GLFW/glfw3.h"
#include <iostream>
#include "io/Input.h"
#include "./gui/_gui.h"
// #include "Models/WindowInfoModel.h"
Graph _g_Graph;

float deltatime = 0.0f;
float lastframe = 0.0f;
float lastX = 400, lastY = 300;
float sensitivity = 0.05f;

void drawBegin();
// void drawMain();
void drawEnd();
void processInput(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

//////////////////////////////////////
//
// 生命周期
//
//////////////////////////////////////
bool Graph::init()
{
    glfwInit(); //初始化GLFW
    //指明OpenGL版本
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
    // float highDPIscaleFactor = 1.0;
    // #ifdef _WIN32
    // if it's a HighDPI monitor, try to scale everything

    // 适配高分屏 ///////////////////////////////////////////////////
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    float xscale, yscale;
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    if (xscale > 1 || yscale > 1)
    {
        this->highDPIscaleFactor = xscale;
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    }
    else
    {
        this->highDPIscaleFactor = 1;
    }
    ////////////////////////////////////////////////////////////////

    // 创建窗口 /////////////////////////////////////////////////////
    this->window = glfwCreateWindow(
        this->windowW,
        this->windowH, "OpenGLTest", NULL, NULL);

    // windowInfoModel.window = window;
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window " << std::endl;
        //销毁所有窗口
        glfwTerminate();
        return false;
    }
    //将该窗口作为当前线程的主上下文
    glfwMakeContextCurrent(window);
    //GLAD是管理OpenGL指针的，在调用任何OpenGL的函数之前需要初始化GLAD
    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    //设置视口Viewport
    //前两个参数控制渲染窗口左下角的相对位置，第三和第四个参数控制渲染窗口的宽度和高度
    //OpenGL会在此窗口大小范围内进行坐标变换
    glViewport(0, 0, 1080, 960);
    //监听窗口大小变化

    _Gui.init();
    return true;
}

///////////////////////////////////////////////////////////////////////

// 绘制相关 /////////////////////////////////////////////////////////
void Graph::drawMesh()
{
    //遍历需要绘制的区块网格
    for (int i = 0; i < chunks2Draw.size(); i++)
    {
        chunks2Draw[i]->draw();
    }
}

void Graph::addChunk2DrawList(std::shared_ptr<Chunk> chunkPtr)
{

    chunks2Draw.push_back(chunkPtr);
    chunkPtr->constructMesh();
}
void Graph::doDraw()
{
    drawBegin();
    // drawMain();
    drawMesh();
    _Gui.renderGui();
    _Gui.drawGui(); //绘制gui，最后一步做
    drawEnd();
}
inline void drawBegin()
{
    // float currenttime = (float)glfwGetTime();
    // deltatime = currenttime - lastframe;
    // lastframe = currenttime;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 开启面剔除
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

// inline void drawMain()
// {
//     // if (GuiSys::isRender)
//     // {
//     // MapDrawer::getInstance()->doDraw();
//     // }

//     //绘制chunk网格

// }

inline void drawEnd()
{
    //将存储在缓冲区中的像素颜色进行绘制，这里涉及到双缓冲的问题
    glfwSwapBuffers(_g_Graph.window);
    //检查有没有触发什么事件（键盘输入、鼠标移动等)、窗口改变
    glfwPollEvents();
    // glfwSetKeyCallback(_Graph.window, processInput);
    // glfwSetCursorPosCallback(_Graph.window, mouse_callback);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     //     float xoffset = (float)(xpos - lastX);
//     //     float yoffset = (float)(lastY - ypos);
//     //     lastX = (float)xpos;
//     //     lastY = (float)ypos;
//     //     xoffset *= sensitivity;
//     //     yoffset *= sensitivity;
//     //     MapDrawer::getInstance()->UpdateView(xoffset, yoffset);
//     // }
// }
// void processInput(GLFWwindow *window, int key, int scancode, int action, int mode)
// {
//     //     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     //         glfwSetWindowShouldClose(window, true);
//     //     if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Forward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Leftward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Backward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Rightward(deltatime*20.0f);
//     // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//     //     MapDrawer::getInstance()->UpdateView(0.01f, 0.01f);
// }
