
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Chunk
        {
            class Manager;
        }
    }
}
////////////////////////////////
#ifndef __CHUNK_MANAGER_H__
#define __CHUNK_MANAGER_H__
#include "./chunk_key.h"
#include "./chunk.h"
#include "ThreadPool.h"
// struct Key;
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Chunk
        {
            class Manager
            {
                /******************
     * datas
    *******************/
            private:
                // Game &game;
                /* data */
                phmap::flat_hash_map<Key, std::shared_ptr<Chunk>> Key2chunkPtr;

                const int ChunkLoadRangeRadius = 3; //加载区块的半径

                /**
     * 需要加载区块相对坐标，用于区块变更时重新加载
    */
                std::vector<Key> inRangeChunksPos;
                //用于遍历并绘制所有网格
                //玩家区块变更就需要更新这个列表

            public:
                /**
     * 要被清除的区块
     *  人物移动的时候，大小是动态变化的，所以用list
    */
                std::list<std::shared_ptr<Chunk>> chunksDestroyQuene;

                /**
     * 要被绘制的区块
     *  大小基本固定，所以用vector
    */
                std::vector<std::shared_ptr<Chunk>> chunks2Draw;

                std::shared_ptr<ThreadPool> threadPool2BuildChunkMeshes;

                /******************
     * funcs
    *******************/
            public:
                bool isChunkInRange(int x, int y, int z,
                                    int centerX = 0, int centerY = 0, int centerZ = 0)
                {
                    x = x - centerX;
                    y = y - centerY;
                    z = z - centerZ;
                    return (x * x + y * y + z * z < ChunkLoadRangeRadius * ChunkLoadRangeRadius);
                }
                inline bool isChunkInRange(const Key &ck,
                                           int centerX = 0, int centerY = 0, int centerZ = 0)
                {
                    return isChunkInRange(ck.x, ck.y, ck.z, centerX, centerY, centerZ);
                }

                Manager();

                //尝试通过Key获取chunk，若未加载，返回null
                std::shared_ptr<Chunk> getLoadedChunkOfKey(const Key &ck)
                {
                }

                //通过Key获取chunk，若不存在则创建chunk
                std::shared_ptr<Chunk> getChunkOfKey(Key &ck)
                {
                    if (!Key2chunkPtr.contains(ck))
                    {
                        auto newChunkPtr = std::make_shared<Chunk>(ck);
                        Key2chunkPtr[ck] = newChunkPtr;
                        //新建区块，在区块初始化过程中应该要向服务器请求数据
                        //暂时还没有服务器联调，所以默认给个区块数据就行
                    }
                    return Key2chunkPtr[ck];
                }
                // void addNewChunk(int32_t x, int32_t y, int32_t z);

                /**
     * 根据计算完的激活标志更新所有区块中的方块物理碰撞
    */
                void updateAllChunkPhysic();

                /**
     * 在重新遍历所有碰撞实体前，将所有区块的激活标志置0
    */
                void resetAllChunkInactived();

                void checkPlayerChunkPosChanged();
            };
        }
    }
}
#endif // __CHUNK_MANAGER_H__