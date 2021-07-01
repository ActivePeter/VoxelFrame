#ifndef VF_ChunkWidth
#define VF_ChunkWidth 16
#define VF_ChunkSize (VF_ChunkWidth * VF_ChunkWidth * VF_ChunkWidth)
#endif

class Chunk;

/////////////////////////////////////////////////
#ifndef __CHUNK_H__
#define __CHUNK_H__
// heads ///////////////////////////
#include "parallel_hashmap/phmap.h"
// #include "chunk_key.h"
#include "graph/Mesh.h"
#include "graph/_Graph.h"
// #include "game.h"
#include "app.h"
#include "block.h"
#include "game.h"
struct ChunkKey
{
    int32_t x;
    int32_t y;
    int32_t z;

    bool operator==(const ChunkKey &o) const
    {
        return x == o.x && y == o.y && z == o.z;
    }
    friend size_t hash_value(const ChunkKey &p)
    {
        return phmap::HashState().combine(0, p.x, p.y, p.z);
    }

    ChunkKey(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z)
    {
    }
    /**
     * 获取一个整数点对应的chunk坐标
    */
    template <typename PosVType>
    static void getChunkKeyOfPoint(ChunkKey &_return, PosVType x, PosVType y, PosVType z);
    /**
     * 获取一个点对应的chunk坐标
    */
    // static void getChunkKeyOfPoint(ChunkKey &_return, float x, float y, float z);
    // ChunkKey(float px, float py, float pz);
    ChunkKey() {}
};
class Chunk : public Mesh
{
private:
    /* data */
    inline uint8_t readData(int x, int y, int z)
    {
        return data[x + y * VF_ChunkWidth + z * VF_ChunkWidth * VF_ChunkWidth];
    }
    inline uint32_t getIndexByPos(int x, int y, int z)
    {
        return x + y * (VF_ChunkWidth + 1) + z * (VF_ChunkWidth + 1) * (VF_ChunkWidth + 1);
    }
    /** 
     * 判断并构建一个方向上的网格 需要参数一一对应
     */
    void constructMeshInOneDim(
        int blockx, int blocky, int blockz,
        int blockx_p, int blocky_p, int blockz_p,
        uint8_t &block,
        uint8_t &block_p,
        CommonBlockInfo &blockInfo,
        CommonBlockInfo &blockInfo_p,
        BlockAbout::FaceDirection posDir,
        BlockAbout::FaceDirection negDir);

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
    bitset<VF_ChunkSize> blockActiveState;

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

    static inline int blockPos2blockIndex(int x, int y, int z)
    {
        return x + y * VF_ChunkWidth + z * VF_ChunkWidth * VF_ChunkWidth;
    }
    static inline void blockIndex2blockPos(int index, int &returnX, int &returnY, int &returnZ)
    {
        returnX = index % VF_ChunkWidth;
        returnY = (index / VF_ChunkWidth) % VF_ChunkWidth;
        returnZ = index / VF_ChunkWidth / VF_ChunkWidth;
    }
};
#include "chunk.temp.h"
#endif // __CHUNK_H__