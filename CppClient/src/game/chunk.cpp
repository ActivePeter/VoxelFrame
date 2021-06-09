#include "chunk.h"
#include "app.h"
#include "enum.h"

void ChunkManager::addNewChunk(int32_t x, int32_t y, int32_t z)
{
    ChunkKey ck(x, y, z);
    auto newChunk = std::make_shared<Chunk>(ck);

    // newChunk->constructMesh();
    chunkKey2chunkPtr[ck] = newChunk;
    App::getInstance().graphPtr->addChunk2DrawList(newChunk);
}

void Chunk::constructMesh()
{
    //仅改变size，实际内存占用不变
    indices.clear();
    vertices.clear();
    // if (vertices.size() != (ChunkWidth + 1) * (ChunkWidth + 1) * (ChunkWidth + 1))
    // {
    //     vertices.resize((ChunkWidth + 1) * (ChunkWidth + 1) * (ChunkWidth + 1));
    //     for (int x = 0; x < ChunkWidth + 1; x++)
    //     {
    //         for (int y = 0; y < ChunkWidth + 1; y++)
    //         {
    //             for (int z = 0; z < ChunkWidth + 1; z++)
    //             {
    //                 vertices[x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1)].setPostion(x, y, z);
    //                 // std::cout << vertices[x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1)].Position.x << ","
    //                 //           << vertices[x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1)].Position.y << ","
    //                 //           << vertices[x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1)].Position.z
    //                 //           << std::endl;
    //             }
    //         }
    //     }
    // }
    auto blockManager = App::getInstance().gamePtr->blockManager;
    //遍历区块
    for (int x = 0; x < ChunkWidth - 1; x++)
    {
        for (int y = 0; y < ChunkWidth - 1; y++)
        {
            for (int z = 0; z < ChunkWidth - 1; z++)
            {
                //标准方块8个点序列对应的在区块中的索引
                // uint32_t _8points[8] = {
                //     getIndexByPos(x + 0, y + 0, z + 0),
                //     getIndexByPos(x + 1, y + 0, z + 0),
                //     getIndexByPos(x + 0, y + 1, z + 0),
                //     getIndexByPos(x + 0, y + 0, z + 1),
                //     getIndexByPos(x + 1, y + 1, z + 0),
                //     getIndexByPos(x + 0, y + 1, z + 1),
                //     getIndexByPos(x + 1, y + 0, z + 1),
                //     getIndexByPos(x + 1, y + 1, z + 1),
                // };

                auto _block = readData(x, y, z);
                auto &blockInfo = blockManager->getBlockInfo(_block);

                auto _block_p = readData(x + 1, y, z);
                auto &blockInfo_p_x = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(x, y, z,
                                      x + 1, y, z,
                                      _block, _block_p, blockInfo, blockInfo_p_x,
                                      BlockAbout::FaceX_Positive, BlockAbout::FaceX_Negative);

                _block_p = readData(x, y + 1, z);
                auto &blockInfo_p_y = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(x, y, z,
                                      x, y + 1, z,
                                      _block, _block_p, blockInfo, blockInfo_p_y,
                                      BlockAbout::FaceY_Positive, BlockAbout::FaceY_Negative);

                _block_p = readData(x, y, z + 1);
                auto &blockInfo_p_z = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(x, y, z,
                                      x, y, z + 1,
                                      _block, _block_p, blockInfo, blockInfo_p_z,
                                      BlockAbout::FaceZ_Positive, BlockAbout::FaceZ_Negative);
            }
        }
    }
    setupMesh();
}

void Chunk::constructMeshInOneDim(int blockx, int blocky, int blockz,
                                  int blockx_p, int blocky_p, int blockz_p,
                                  uint8_t &block,
                                  uint8_t &block_p,
                                  CommonBlockInfo &blockInfo,
                                  CommonBlockInfo &blockInfo_p,
                                  BlockAbout::FaceDirection posDir,
                                  BlockAbout::FaceDirection negDir)
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
