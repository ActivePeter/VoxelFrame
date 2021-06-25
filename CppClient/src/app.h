class App;

#ifndef __APP_H__
#define __APP_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "base.h"
#include "paecs/paecs.h"
#include "game/game.h"
#include "graph/_Graph.h"
#include "net/_net.h"
#include "system_related/_Input.h"
// #include "system/io/_IO.h"
// #include "s"

////////////////////////////////////////
// struct A
// {
//     int id;
// };
// struct B
// {
//     int id;
//     char testChar;
// };

// void helloworld_sys(B &a);

//the global one
//全局唯一单例 存储，访问 所有动静态资源
class App
{
private:
    /* data */
public:
    // Scene scene;
    std::shared_ptr<paecs::Scene> ecsPtr;
    std::shared_ptr<Game> gamePtr;
    std::shared_ptr<Graph> graphPtr;
    std::shared_ptr<Input> inputPtr;

    // timing
    float deltaTime = 0.0f; // time between current frame and last frame
    float lastFrame = 0.0f;

    // app()
    // {

    // }
    inline void calcTimePerLoop()
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    void run();
    static App &getInstance();
};

// extern app _g_app;
#endif // __APP_H__