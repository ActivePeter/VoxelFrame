#include "chunk_manager.h"

namespace N_Chunk_Manager
{
    void checkPlayerChunkPosChanged(Game &game)
    {
        game.chunkManager->checkPlayerChunkPosChanged();
    }
    /**
     * 更新区块清除列表中区块的状态
     *      1.若在范围内，则从销毁列表中清除
     *      2.不在范围内，进行倒计时，
     *      3.若倒计时为0，则执行清除
    */
    void updateChunksDestroyState(Game &game)
    {
        auto &destroyQuene = game.chunkManager->chunksDestroyQuene;
        if (destroyQuene.size() > 0)
        {
            // int cnt = 0;
            for (auto iter = destroyQuene.begin(); iter != destroyQuene.end();)
            {
                // std::cout << "left destroy quene cnt " << cnt << std::endl;
                // cnt++;
                *iter++;
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
    //构造区块网格的线程池
    threadPool2BuildChunkMeshes = make_shared<ThreadPool>(4);

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
                        //创建chunkkey
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
        App::getInstance()
            .gamePtr
            ->registTCallback(1,
                              N_Chunk_Manager::checkPlayerChunkPosChanged);
        App::getInstance()
            .gamePtr
            ->registTCallback(50,
                              N_Chunk_Manager::updateChunksDestroyState);
    }
    // addNewChunk(0, 0, 0);
}

void ChunkManager::updateAllChunkPhysic()
{
    for (auto &i : this->chunks2Draw)
    {
        i->updatePhysic();
    }
}

void ChunkManager::resetAllChunkInactived()
{
    for (auto &i : this->chunks2Draw)
    {
        i->resetAllBlock2inactive();
    }
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
    static int lastX = -1, lastY = -1, lastZ = -1;
    auto playerPtr = App::getInstance().gamePtr->mainPlayer;
    auto &player = *playerPtr;
    if (lastX != player.chunkX ||
        lastY != player.chunkY ||
        lastZ != player.chunkZ)
    { //如果改变，就重新计算范围内区块
        std::list<std::shared_ptr<Chunk>> newInRangeChunks;
        //遍历原来的区块，把原来的旧的区块加入销毁列表
        for (int i = 0; i < chunks2Draw.size(); i++)
        {
            if (chunks2Draw[i])
            {
                if (!isChunkInRange(chunks2Draw[i]->chunkKey), player.chunkX, player.chunkY, player.chunkZ)
                {
                    chunksDestroyQuene.push_back(chunks2Draw[i]);
                }
            }
        }
        //遍历球体范围的区块
        for (int i = 0; i < inRangeChunksPos.size(); i++)
        {
            auto &cur = inRangeChunksPos[i];
            auto chunk2Draw = getChunkOfKey(ChunkKey(
                player.chunkX + cur.x,
                player.chunkY + cur.y,
                player.chunkZ + cur.z));
            chunks2Draw[i] = chunk2Draw;

            //这里的 construct mesh 要换成多线程
            //往线程池加入构造网格函数
            /**
             * 出现了一个bug
             * 在draw chunk时 chunk似乎被释放了
             * 发现是因为gl的函数不能被多线程调用，即使是无关函数，也可能操作相关数据
             * 
             * 又有了一个问题，纵向移动时一加载区块就直接无法操作，也不是无响应
            */
            // auto &chunkR = *chunk2Draw;
            threadPool2BuildChunkMeshes->enqueue(
                [](std::shared_ptr<Chunk> chunkPtr) { // Chunk *chunkPtr)
                    // chunkPtr->dataMut.lock();
                    chunkPtr->constructMesh();
                    // chunkPtr->dataMut.unlock();
                    // chunks2Draw[i] = chunk2Draw;
                },
                chunk2Draw);
            // chunks2Draw[i]->constructMesh();
        }
    }
    // std::cout << "checkPlayerChunkPosChanged" << std::endl;
    // printf("checkPlayerChunkPosChanged %d,%d,%d",
    //        player.chunkX,
    //        player.chunkY,
    //        player.chunkZ);

    lastX = player.chunkX;
    lastY = player.chunkY;
    lastZ = player.chunkZ;
}
