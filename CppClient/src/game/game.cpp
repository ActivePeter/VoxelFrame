#include "game.h"

void Game::start()
{
    //因为game是父元素，所以传给子元素引用就行，game管理子元素的生命周期
    chunkManager = std::make_shared<ChunkManager>();
    blockManager = std::make_shared<BlockManager>();
    mainPlayer = std::make_shared<MainPlayer>();
    // chunkManager->addNewChunk(0, 0, 0);

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
        foundIndex = TCallers.size() - 1;
    }
    TCallers[foundIndex].callbacks.push_back(f);
}