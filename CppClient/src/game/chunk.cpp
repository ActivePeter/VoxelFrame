#include "chunk.h"
#include "app.h"
#include "enum.h"
// N_Chunk /////////////////////////////////////////////////////////////////////////////////////////

// Chunk /////////////////////////////////////////////////////////////////////////////////////////

/**
 * 多线程访问函数
 * 
 * //首次加载、数据变更（修改地形，都要构造（前提是在视野内
 * 构造的时候要给indices 和vertices 加锁
 * 
*/
void Chunk::constructMesh()
{
    dataMut.lock();
    // 貌似不用加锁，因为访问顶点数据的只可能时这个函数

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
    for (int x = 0; x < VF_ChunkWidth - 1; x++)
    {
        for (int y = 0; y < VF_ChunkWidth - 1; y++)
        {
            for (int z = 0; z < VF_ChunkWidth - 1; z++)
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
    dataMut.unlock();

    // dataMut.lock();
    needSetupBeforeDraw = true;
    indicesSize = (int)indices.size();
    printf("chunk %d %d %d is constructed\r\n", chunkKey.x, chunkKey.y, chunkKey.z);

    // setupMesh();
}

/**
 * 构造chunk
 * 测试阶段初始化数组为一半土方快，一半空
*/
Chunk::Chunk(ChunkKey ck)
{
    chunkKey = ck;
    mesh_position.x = (float)(ck.x * VF_ChunkWidth);
    mesh_position.y = (float)(ck.y * VF_ChunkWidth);
    mesh_position.z = (float)(ck.z * VF_ChunkWidth);

    for (int x = 0; x < VF_ChunkWidth; x++)
    {
        for (int y = 0; y < VF_ChunkWidth; y++)
        {
            for (int z = 0; z < VF_ChunkWidth; z++)
            {
                if (y > VF_ChunkWidth / 2)
                {
                    if (x == 8 && z == 8)
                    {
                        data[Chunk::blockPos2blockIndex(x, y, z)] = 1;
                    }
                    else
                    {
                        data[Chunk::blockPos2blockIndex(x, y, z)] = 0;
                    }
                }
                else
                {
                    data[Chunk::blockPos2blockIndex(x, y, z)] = 1;
                }
            }
        }
    }
    memset(this->blockRigids, 0, sizeof(this->blockRigids));
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
        // printf("vec added 1: %.2f %.2f %.2f \r\n", vetex1.Position.x, vetex1.Position.y, vetex1.Position.z);
        // printf("vec added 2: %.2f %.2f %.2f \r\n", vetex2.Position.x, vetex2.Position.y, vetex2.Position.z);
        // printf("vec added 3: %.2f %.2f %.2f \r\n", vetex3.Position.x, vetex3.Position.y, vetex3.Position.z);
        // printf("vec added 4: %.2f %.2f %.2f \r\n", vetex4.Position.x, vetex4.Position.y, vetex4.Position.z);
        // printf("\r\n");
    }
    //x为空 x+1为实,添加朝x负向的面
    else if (!block &&
             block_p &&
             blockInfo_p.hasStandardFace(negDir))
    {
        blockInfo_p.pushOneFace2Mesh(blockx_p, blocky_p, blockz_p, negDir, *this);
    }
}

void Chunk::setInRangeBlockActive(int minBx, int minBy, int minBz,
                                  int maxBx, int maxBy, int maxBz)
{
    // printf_s("setInRangeBlockActive\r\n");
    // printf_s("%d %d %d\r\n", minBx, minBy, minBz);

    // printf_s("%d %d %d\r\n", maxBx, maxBy, maxBz);
    for (int bx = minBx; bx <= maxBx; bx++)
    {
        for (int by = minBy; by <= maxBy; by++)
        {
            for (int bz = minBz; bz <= maxBz; bz++)
            {
                auto index = Chunk::blockPos2blockIndex(bx, by, bz);
                this->blockActiveState[index / 8] |= 0x01 << (index % 8);
                // this->blockActiveState.set(Chunk::blockPos2blockIndex(bx, by, bz));
            }
        }
    }
}

void Chunk::updatePhysic()
{
    // printf_s("sizeof blockActiveState\r\n");
    // printf_s("%d\r\n", sizeof(blockActiveState));
    for (int i = 0; i < VF_ChunkSize; i++)
    {
        bool state = blockActiveState[i / 8] & (0x01 << (i % 8));
        if (state)
        {
            int bx, by, bz;
            Chunk::blockIndex2blockPos(i, bx, by, bz);
            //lazy load
            if (!blockRigids[i])
            {

                blockRigids[i] = physic_engine::physicWorld().createRigidBody(
                    rp3d::Transform(
                        rp3d::Vector3(this->chunkKey.x * VF_ChunkWidth + bx,
                                      this->chunkKey.y * VF_ChunkWidth + by,
                                      this->chunkKey.z * VF_ChunkWidth + bz),
                        rp3d::Quaternion::identity()));
                //同时要根据方块类型配置它的collider
                blockRigids[i]->setType((rp3d::BodyType::STATIC));

                if (this->data[i])
                {
                    blockRigids[i]->addCollider(
                        App::getInstance().gamePtr->blockManager->getBlockInfo(i).getBlockColliderShape(),
                        rp3d::Transform(
                            rp3d::Vector3(0.5, 0.5, 0.5),
                            rp3d::Quaternion::identity()));

                    blockRigids[i]->getCollider(0)->getMaterial().setBounciness(0);
                }
            }
            if (this->data[i])
            {
                // printf_s("updatePhysic\r\n");
                // printf_s("%d %d %d\r\n", bx, by, bz);
                blockRigids[i]->setIsActive(true);
            }
            else
            {
                //empty block
                blockRigids[i]->setIsActive(false);
            }
        }
        else
        { //inactived
            if (blockRigids[i])
            {
                blockRigids[i]->setIsActive(false);
            }
        }
    }
}