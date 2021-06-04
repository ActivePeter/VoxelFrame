#include "game.h"

void Game::start()
{
    //因为game是父元素，所以传给子元素引用就行，game管理子元素的生命周期
    chunkManager = std::make_shared<ChunkManager>();
    blockManager = std::make_shared<BlockManager>();
    chunkManager->addNewChunk(0, 0, 0);
    // this
}