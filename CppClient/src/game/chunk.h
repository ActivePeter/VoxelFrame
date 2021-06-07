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
        CommonBlockInfo::FaceDirection posDir,
        CommonBlockInfo::FaceDirection negDir)
    {

        //+1为空 当前为实心
        if (!block_p &&
            block &&
            blockInfo.hasStandardFace(posDir))
        {
            blockInfo.pushOneFace2Mesh(blockx, blocky, blockz, posDir, *this);
            auto &mesh = *this;
            auto &vetex1 = mesh.vertices[mesh.vertices.size() - 4];
            auto &vetex2 = mesh.vertices[mesh.vertices.size() - 3];
            auto &vetex3 = mesh.vertices[mesh.vertices.size() - 2];
            auto &vetex4 = mesh.vertices[mesh.vertices.size() - 1];
            printf("vec added 1: %.2f %.2f %.2f \r\n", vetex1.Position.x, vetex1.Position.y, vetex1.Position.z);
            printf("vec added 2: %.2f %.2f %.2f \r\n", vetex2.Position.x, vetex2.Position.y, vetex2.Position.z);
            printf("vec added 3: %.2f %.2f %.2f \r\n", vetex3.Position.x, vetex3.Position.y, vetex3.Position.z);
            printf("vec added 4: %.2f %.2f %.2f \r\n", vetex4.Position.x, vetex4.Position.y, vetex4.Position.z);
            printf("\r\n");
        }
        //x为空 x+1为实,添加朝x负向的面
        else if (!block &&
                 block_p &&
                 blockInfo_p.hasStandardFace(negDir))
        {
            blockInfo_p.pushOneFace2Mesh(blockx_p, blocky_p, blockz_p, negDir, *this);
        }
    }

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

public:
    ChunkManager()
    {
        // addNewChunk(0, 0, 0);
    }
    void addNewChunk(int32_t x, int32_t y, int32_t z);
};