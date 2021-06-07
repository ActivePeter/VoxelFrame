#include "chunk.h"
#include "app.h"

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
                                      CommonBlockInfo::FaceX_Positive, CommonBlockInfo::FaceX_Negative);

                _block_p = readData(x, y + 1, z);
                auto &blockInfo_p_y = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(x, y, z,
                                      x, y + 1, z,
                                      _block, _block_p, blockInfo, blockInfo_p_y,
                                      CommonBlockInfo::FaceY_Positive, CommonBlockInfo::FaceY_Negative);

                _block_p = readData(x, y, z + 1);
                auto &blockInfo_p_z = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(x, y, z,
                                      x, y, z + 1,
                                      _block, _block_p, blockInfo, blockInfo_p_z,
                                      CommonBlockInfo::FaceZ_Positive, CommonBlockInfo::FaceZ_Negative);
            }
        }
    }
    setupMesh();
}
