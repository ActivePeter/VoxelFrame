#include "block.h"
#include "chunk_key.h"
CommonBlockInfo *BlockManager::getBlockInfoByBlockPos(int bx, int by, int bz)
{
    //1.获取区块
    ChunkKey ck;
    ChunkKey::getChunkKeyOfPoint(ck, bx, by, bz);
    auto chunkPtr = App::getInstance().gamePtr->chunkManager->getChunkOfKeyIfLoaded(ck);
    if (!chunkPtr)
    {
        return nullptr;
    }
    //执行这句之后bx。by bz就变成了相对区块坐标了
    chunkPtr->turnInWorldPos2InChunkPos(bx, by, bz);
    // int blockPos = chunkPtr->
    // if (chunkPtr->)
    return &this->commonBlockInfos[chunkPtr->getBlockIdAtPos(bx, by, bz)];
}
