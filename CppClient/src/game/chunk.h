#ifndef VF_ChunkWidth
#define VF_ChunkWidth 16
#define VF_ChunkSize (VF_ChunkWidth * VF_ChunkWidth * VF_ChunkWidth)
#endif

class Chunk;
// struct ChunkKey;

/////////////////////////////////////////////////
#ifndef __VF_CHUNK_H__
#define __VF_CHUNK_H__
// heads ///////////////////////////
#include "parallel_hashmap/phmap.h"
// #include "chunk_key.h"
#include "graph/Mesh.h"
#include "graph/_Graph.h"
// #include "game.h"
// #include "app.h"
#include "block/block.h"
// #include "game.h"
#include "physic_engine/physic_engine.h"

#include "chunk_key.h"

class Chunk : public Mesh
{
private:
    /* data */
    inline uint8_t readData(int x, int y, int z)
    {
        return data[x + y * VF_ChunkWidth + z * VF_ChunkWidth * VF_ChunkWidth];
    }
    // static inline uint32_t getBlockIndexByPos(int x, int y, int z)
    // {
    //     return x + y * (VF_ChunkWidth + 1) + z * (VF_ChunkWidth + 1) * (VF_ChunkWidth + 1);
    // }
    /** 
     * 判断并构建一个方向上的网格 需要参数一一对应
     */
    void constructMeshInOneDim(
        int blockx, int blocky, int blockz,
        int blockx_p, int blocky_p, int blockz_p,
        // uint8_t &block,
        // uint8_t &block_p,
        BlockInfo &blockInfo,
        BlockInfo &blockInfo_p,
        Block_FaceDirection posDir,
        Block_FaceDirection negDir);

public:
    /**
     * 方块id信息
    */
    uint8_t data[VF_ChunkSize];
    /**
     * 方块碰撞器
    */
    rp3d::RigidBody *blockRigids[VF_ChunkSize];
    /**
     * 方块激活状态
    */
    char blockActiveState[VF_ChunkSize / 8];

    //区块坐标（在map中的key
    ChunkKey chunkKey;

    // bool need
    // Game &game;

    void constructMesh();

    /**
     * 在计算完激活状态后
     * 更新active状态到physic上
    */
    void updatePhysic();
    /**
     * 设置范围内的方块为激活状态（加载碰撞器
    */
    void setInRangeBlockActive(int minBx, int minBy, int minBz,
                               int maxBx, int maxBy, int maxBz);

    /**
     * 在重新遍历所有实体以加载区块碰撞器状态之前，将所有方块都设置为未激活
     * 设置范围内的方块为激活状态（加载碰撞器
    */
    void resetAllBlock2inactive()
    {
        // blockActiveState
        memset(&blockActiveState, 0, sizeof(blockActiveState));
    }
    Chunk(ChunkKey ck);
    Chunk() {}

    /**
     * block坐标转换为在chunkdata中的index
    */
    static inline int blockPos2blockIndex(int x, int y, int z)
    {
        return x + y * VF_ChunkWidth + z * VF_ChunkWidth * VF_ChunkWidth;
    }

    /**
     * blockindex转换为block坐标
    */
    static inline void blockIndex2blockPos(int index, int &returnX, int &returnY, int &returnZ)
    {
        returnX = index % VF_ChunkWidth;
        returnY = (index / VF_ChunkWidth) % VF_ChunkWidth;
        returnZ = index / VF_ChunkWidth / VF_ChunkWidth;
    }
};

#include "chunk.temp.h"
// #include "chunk_manager.h"

#endif // __CHUNK_H__