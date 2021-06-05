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
     * @brief 构建一个维度的网格 需要参数一一对应
     * @param block    方块id
     * @param block_p  +1方块的id
     * @param blockInfo 方块信息
     * @param blockInfo_p +1方块信息
     * @param posDir 正方向
     * @param negDir 负方向
     *
     * @return 返回说明
     *     -<em>false</em> fail
     *     -<em>true</em> succeed
     */
    void constructMeshInOneDim(
        uint8_t &block,
        uint8_t &block_p,
        CommonBlockInfo &blockInfo,
        CommonBlockInfo &blockInfo_p,
        CommonBlockInfo::FaceDirection posDir,
        CommonBlockInfo::FaceDirection negDir,
        uint32_t _8points[])
    {
        //+1为空 当前为实心
        if (!block_p &&
            block &&
            blockInfo.hasFace(posDir))
        {
            uint8_t indicesOfIndices[6]; //qaq 取不来名字了
            blockInfo.getFaceIndices(posDir, indicesOfIndices);
            for (int i = 0; i < 6; i++)
            {

                // std::cout << (int)indicesOfIndices[i] << ",";
                indices.push_back(_8points[indicesOfIndices[i]]);
            }
            // std::cout << std::endl;
            //逆时针面为正面
        }
        //x为空 x+1为实,添加朝x负向的面
        else if (!block &&
                 block_p &&
                 blockInfo_p.hasFace(negDir))
        {
            uint8_t indicesOfIndices[6]; //qaq 取不来名字了
            blockInfo_p.getFaceIndices(negDir, indicesOfIndices);
            for (int i = 0; i < 6; i++)
            {
                // std::cout << (int)indicesOfIndices[i] << ".";
                // std::cout << indicesOfIndices[i] << ",";
                indices.push_back(_8points[indicesOfIndices[i]]);
            }

            // std::cout << std::endl;
            //逆时针面为正面
        }
        // std::cout << std::endl;
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