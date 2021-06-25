#include "game.h"
#include "ecs/sys/ColliderSys.h"
/**
 * 
 *game start 之前应当加载完毕所有引擎层内容 
 * 
*/
void Game::start()
{
    //因为game是父元素，所以传给子元素引用就行，game管理子元素的生命周期
    chunkManager = std::make_shared<ChunkManager>();
    blockManager = std::make_shared<BlockManager>();
    mainPlayer = std::make_shared<MainPlayer>();
    // chunkManager->addNewChunk(0, 0, 0);

    //注册锁住摄像头的触发事件
    // registry::game_ControllingSwitch();
    IRegister_regist();
    playing = true;

    App::getInstance()
        .ecsPtr->addSysByFunc(EcsSys::checkCapsuleCollider2aroundChunkData);
    // this
}

/**
 * 游戏内容循环刷新函数
 *   1.判断并调用周期性回调函数
*/
void Game::loop()
{
    for (int i = 0; i < TCallers.size(); i++)
    {
        if (gameTick % TCallers[i].T == 0)
        {
            TCallers[i].callAll(*this);
        }
    }
    App::getInstance().ecsPtr->loop();
    gameTick++;
}
/**注册周期性回调函数
 * 没有重复性检测
 * **/
void Game::registTCallback(int T, TCallbackFunc f)
{
    int foundIndex = -1;
    for (int i = 0; i < TCallers.size(); i++)
    {
        if (TCallers[i].T == T)
        {
            foundIndex = i;
            //找到了
            break;
        }
    }
    if (foundIndex == -1)
    {
        TCallers.push_back(TCaller(T));
        foundIndex = (int)TCallers.size() - 1;
    }
    TCallers[foundIndex].callbacks.push_back(f);
}
void Game::IRegister_regist()
{
    //set focus when playing
    // auto &game = *this;
    auto &input = *App::getInstance().inputPtr;
    input.registerMouseClick(
        [](int btn, int action)
        {
            auto &game = *App::getInstance().gamePtr;
            if (btn == M_Input_MOUSE_BUTTON_LEFT && action == Input_KeyState::E_KeyDown)
            {
                if (game.playing)
                {
                    App::getInstance().graphPtr->gameWindow.cursor.setLocked(true);
                }
            }
        });
    input.registerProcessInput(
        [](Input &input)
        {
            if (input.getKey(M_Input_KEY_ESCAPE))
            {
                App::getInstance().graphPtr->gameWindow.cursor.setLocked(false);
            }
            // auto &app = App::getInstance();
            // auto window = App::getInstance().graphPtr->gameWindow.window;
            // if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            // {
            // }
        });
}
