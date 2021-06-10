#include "chunk_manager.h"
namespace N_Chunk_Manager
{
    void checkPlayerChunkPosChanged(Game &game)
    {
        game.chunkManager->checkPlayerChunkPosChanged();
    }
    /**
     * 更新区块清除列表中区块的状态
    */
    void updateChunksDestroyState(Game &game)
    {
        auto &destroyQuene = game.chunkManager->chunksDestroyQuene;
        if (destroyQuene.size() > 0)
        {
            for (auto iter = destroyQuene.begin(); iter != destroyQuene.end();)
            {
                // iter->copyTo(imageROI);
                // blockFacesBuffer.erase(iter++);
            }
        }
    }
}

// ChunkManager /////////////////////////////////////////////////////////////////////////////////////////
// void ChunkManager::addNewChunk(int32_t x, int32_t y, int32_t z)
// {
//     ChunkKey ck(x, y, z);
//     auto newChunk = std::make_shared<Chunk>(ck);

//     // newChunk->constructMesh();
//     chunkKey2chunkPtr[ck] = newChunk;
//     App::getInstance().graphPtr->addChunk2DrawList(newChunk);
// }

/**
 * 构造chunkManager
 * 1.构造视野区块数组
 * 2.注册区块相关的周期检测
*/
ChunkManager::ChunkManager()
{
    //1.构造视野区块数组
    {
        inRangeChunksPos.resize(
            (2 * ChunkLoadRangeRadius - 1) *
            (2 * ChunkLoadRangeRadius - 1) *
            (2 * ChunkLoadRangeRadius - 1));
        int cnt = 0;
        for (int x = -ChunkLoadRangeRadius + 1; x < ChunkLoadRangeRadius; x++)
        {
            for (int y = -ChunkLoadRangeRadius + 1; y < ChunkLoadRangeRadius; y++)
            {
                for (int z = -ChunkLoadRangeRadius + 1; z < ChunkLoadRangeRadius; z++)
                {
                    //如果在范围内。加入inRangeChunkPos
                    if (isChunkInRange(x, y, z))
                    {
                        inRangeChunksPos[cnt] = ChunkKey(x, y, z);
                        cnt++;
                    }
                }
            }
        }
        inRangeChunksPos.resize(cnt);
        chunks2Draw.resize(cnt);
    }

    // 2.注册区块相关的周期检测
    {
        App::getInstance().gamePtr->registTCallback(1, N_Chunk_Manager::checkPlayerChunkPosChanged);
        App::getInstance().gamePtr->registTCallback(50, N_Chunk_Manager::updateChunksDestroyState);
    }
    // addNewChunk(0, 0, 0);
}

/**
 * 如果玩家所在区块。就需要加载新的未绘制的区块，
 * 同时将不在视野内的区块加入倒计时销毁队列
 * 当然，如果在时间内又再次回来。那么将区块再次从销毁队列中移除
 * 
 * 思考
 * 用什么来做销毁队列：易于遍历和增删，
 * 目前来看可以用list，list增删方便 遍历也不差
*/
void ChunkManager::checkPlayerChunkPosChanged()
{
    //上一次player所在区块的坐标
    static int lastX = 0, lastY = 0, lastZ = 0;
    auto &player = *App::getInstance().gamePtr->mainPlayer;
    if (lastX != player.chunkX ||
        lastY != player.chunkY ||
        lastZ != player.chunkZ)
    { //如果改变，就重新计算范围内区块
        std::list<std::shared_ptr<Chunk>> newInRangeChunks;
        //遍历原来的区块，把原来的旧的区块加入销毁列表
        for (int i = 0; i < chunks2Draw.size(); i++)
        {
            if (!isChunkInRange(chunks2Draw[i]->chunkKey), player.chunkX, player.chunkY, player.chunkZ)
            {
                chunksDestroyQuene.push_back(chunks2Draw[i]);
            }
        }
        //遍历球体范围的区块
        for (int i = 0; i < inRangeChunksPos.size(); i++)
        {
            auto &cur = inRangeChunksPos[i];
            chunks2Draw[i] = getChunkOfKey(ChunkKey(
                player.chunkX + cur.x,
                player.chunkY + cur.y,
                player.chunkZ + cur.z));
        }
    }
}
