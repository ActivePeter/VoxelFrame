#include "App.h"

void App::run()
{
    ecsPtr = paecs::createScene();
    gamePtr = std::make_shared<VF::_Game::Game>();
    graphPtr = std::make_shared<VF::_Graph::Graph>();
    inputPtr = std::make_shared<Input>();
    auto &graph = *graphPtr;
    if (!graph.init())
    {
        return; //启动失败
    }
    inputPtr->init();

    // ecs.createEntity()
    //     .addEmptyComponent<A>()
    //     .addEmptyComponent<B>();
    // ecs.addSysByFunc(helloworld_sys);
    // _g_net.start();
    // NetSys::start();
    // WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
    gamePtr->start();
    while (graph.running())
    {
        calcTimePerLoop();
        inputPtr->processInput();
        // DrawSys::doDraw();
        graph.doDraw();
        gamePtr->loop();
        // //清屏
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // ecs.loop();
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
    graph.end();
}

App &App::getInstance()
{
    //位于堆区，自创建时就存在
    static App instance;
    return instance;
}

// void helloworld_sys(B &a)
// {
//     std::cout << "helloworld" << std::endl;
// }
