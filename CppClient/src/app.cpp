#include "App.h"

void App::run()
{
    ecsPtr = paecs::createScene();
    gamePtr = std::make_shared<Game>();

    if (!_g_Graph.init())
    {
        return; //启动失败
    }

    auto &ecs = *ecsPtr;
    ecs.createEntity()
        .addEmptyComponent<A>()
        .addEmptyComponent<B>();
    ecs.addSysByFunc(helloworld_sys);
    // _g_net.start();
    // NetSys::start();
    // WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
    gamePtr->start();
    while (_g_Graph.running())
    {
        // DrawSys::doDraw();
        _g_Graph.doDraw();
        // //清屏
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        ecs.loop();
    }

    // //循环渲染，在退出前一直不断地绘制图像
    // while (!glfwWindowShouldClose(_g_Graph.window))
    // {
    //     // DrawSys::doDraw();
    //     _g_Graph.doDraw();
    //     // //清屏
    //     // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //     // glClear(GL_COLOR_BUFFER_BIT);
    // }

    // // 退出前清理
    _g_Graph.end();
}

App &App::getInstance()
{

    static App instance;
    return instance;
}

void helloworld_sys(B &a)
{
    std::cout << "helloworld" << std::endl;
}
