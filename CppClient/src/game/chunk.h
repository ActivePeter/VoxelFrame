#pragma once
#include "parallel_hashmap/phmap.h"
#include "graph/Mesh.h"
#include "graph/_Graph.h"
// #include "game.h"
#include "app.h"
#include "block.h"

#define ChunkWidth 64
#define ChunkSize (ChunkWidth * ChunkWidth * ChunkWidth)

// class Game;
class Mesh;
class CommonBlockInfo;
//////////////////////////
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
    ChunkKey() {}
};
class Chunk : public Mesh
{
private:
    /* data */
    inline uint8_t readData(int x, int y, int z)
    {
        return data[x + y * ChunkWidth + z * ChunkWidth * ChunkWidth];
    }
    inline uint32_t getIndexByPos(int x, int y, int z)
    {
        return x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1);
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
    uint8_t data[ChunkSize];
    ChunkKey chunkKey;
    // Game &game;

    //首次加载、数据变更（修改地形，都要构造（前提是在视野内
    void constructMesh();

    Chunk(ChunkKey ck)
    {
        chunkKey = ck;
        for (int x = 0; x < ChunkWidth; x++)
        {
            for (int y = 0; y < ChunkWidth; y++)
            {
                for (int z = 0; z < ChunkWidth; z++)
                {
                    if (y > ChunkWidth / 2)
                    {
                        data[x + y * ChunkWidth + z * ChunkWidth * ChunkWidth] = 0;
                    }
                    else
                    {
                        data[x + y * ChunkWidth + z * ChunkWidth * ChunkWidth] = 1;
                    }
                }
            }
        }
    }
    Chunk() {}
};

class ChunkManager
{
private:
    // Game &game;
    /* data */
    phmap::flat_hash_map<ChunkKey, std::shared_ptr<Chunk>> chunkKey2chunkPtr;
    std::list<std::shared_ptr<Chunk>> chunksDestroyQuene;

public:
    ChunkManager()
    {
        // addNewChunk(0, 0, 0);
    }
    void addNewChunk(int32_t x, int32_t y, int32_t z);

    void checkPlayerChunkPosChanged();
};