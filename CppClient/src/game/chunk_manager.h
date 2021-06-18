
class ChunkManager;
////////////////////////////////
#ifndef __CHUNK_MANAGER_H__
#define __CHUNK_MANAGER_H__
#include "chunk_key.h"
#include "chunk.h"
#include "ThreadPool.h"

class ChunkManager
{
    /******************
     * datas
    *******************/
private:
    // Game &game;
    /* data */
    phmap::flat_hash_map<ChunkKey, std::shared_ptr<Chunk>> chunkKey2chunkPtr;

    const int ChunkLoadRangeRadius = 3; //加载区块的半径

    /**
     * 需要加载区块相对坐标，用于区块变更时重新加载
    */
    std::vector<ChunkKey> inRangeChunksPos;
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
    inline bool isChunkInRange(const ChunkKey &ck,
                               int centerX = 0, int centerY = 0, int centerZ = 0)
    {
        return isChunkInRange(ck.x, ck.y, ck.z, centerX, centerY, centerZ);
    }

    ChunkManager();
    std::shared_ptr<Chunk> getChunkOfKey(ChunkKey &ck)
    {
        if (!chunkKey2chunkPtr.contains(ck))
        {
            auto newChunkPtr = std::make_shared<Chunk>(ck);
            chunkKey2chunkPtr[ck] = newChunkPtr;
            //新建区块，在区块初始化过程中应该要向服务器请求数据
            //暂时还没有服务器联调，所以默认给个区块数据就行
        }
        return chunkKey2chunkPtr[ck];
    }
    // void addNewChunk(int32_t x, int32_t y, int32_t z);

    void checkPlayerChunkPosChanged();
};
#endif // __CHUNK_MANAGER_H__