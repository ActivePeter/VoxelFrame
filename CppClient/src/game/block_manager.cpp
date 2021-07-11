#include "block.h"
CommonBlockInfo *BlockManager::getBlcokInfoByBlockPos(int bx, int by, int bz)
{
    //1.获取区块
    App::getInstance().gamePtr->chunkManager->getChunkOfKeyIfLoaded();
}
