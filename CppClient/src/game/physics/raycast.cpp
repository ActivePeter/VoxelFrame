#include "raycast.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace Physics
        {
            static bool raycast2Triangle(
                const glm::vec3 &startPoint,
                const glm::vec3 &direction, const glm::vec3 &triP1, const glm::vec3 &triP2, const glm::vec3 &triP3,
                glm::vec3 &return_cross)
            {
                //应当在前面先判断下是否平行，若平行则直接不相交
                //法向量
                auto norm = glm::cross(triP2 - triP1, triP3 - triP1);
                //如果两个向量垂直浮点数不能直接判断等于0，要跟epsilon做比较
                if (abs(glm::dot(direction, norm)) < std::numeric_limits<float>::epsilon())
                {
                    return false;
                }
                //起点到三角形三点的向量矩阵
                glm::mat3x3 p2tvs(triP1 - startPoint, triP2 - startPoint, triP3 - startPoint);
                glm::vec3 k1k2k3 = glm::inverse(p2tvs) * direction;
                float n = 1 / (k1k2k3.x + k1k2k3.y + k1k2k3.z);
                return_cross = startPoint + (n)*direction;
                float a = n * k1k2k3.x;
                float b = n * k1k2k3.y;
                float c = n * k1k2k3.z;
                //全都大于0即在三角形内
                if (a >= 0 && b >= 0 && c >= 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            static bool raycast2TrianglesNearest(
                const Type::Vec3F &startPoint, const Type::Vec3F &direction,
                std::vector<Type::Vec3F> &vertexPoses, _Graph::Indices &indices, Type::Vec3F &return_colidPoint)
            {
                assert(indices.size() % 3 == 0);
                //遍历所有三角形
                for (size_t i = 0; i < indices.size() / 3; i++)
                {
                }
            }
            static void raycast2ChunkAndReturnBlock(
                const glm::vec3 &startPoint,
                const glm::vec3 &direction,
                float maxRange,
                std::vector<_Chunk::Chunk> &return_chunkPtr,
                int &return_blockIndexInChunk)
            {
                glm::vec3 delta = direction / VF::_Calc::vec3Len(direction) * maxRange;
                glm::vec3 endPointF = startPoint + delta;

                int endX = floor(endPointF.x);
                int endY = floor(endPointF.y);
                int endZ = floor(endPointF.z);

                int curX = floor(startPoint.x);
                int curY = floor(startPoint.y);
                int curZ = floor(startPoint.z);

                char dirX = 0, dirY = 0, dirZ = 0;

                dirX = endX > curX ? 1 : dirX;
                dirY = endY > curY ? 1 : dirY;
                dirZ = endZ > curZ ? 1 : dirZ;

                // dirX = endX < curX ? -1 : dirX;
                // dirY = endY < curY ? -1 : dirY;
                // dirZ = endZ < curZ ? -1 : dirZ;
                //未扫描到底，
                while (curX != endX || curY != endY || curZ != endZ)
                {
                    //1.找到最先经过的方块
                    //  x+1
                    float borderX = curX + dirX;
                    float borderY = curY + dirY;
                    float borderZ = curZ + dirZ;

                    float scaleX = (borderX - startPoint.x) / delta.x;
                    float scaleY = (borderY - startPoint.y) / delta.y;
                    float scaleZ = (borderZ - startPoint.z) / delta.z;
                    if (scaleZ > scaleX && scaleY > scaleX)
                    {
                        //scaleX is min
                        curX++;
                    }
                    else if (scaleZ > scaleY)
                    {
                        //scaleY is min
                        curY++;
                    }
                    else
                    {
                        //scaleZ is min
                        curZ++;
                    }

                    //2.判断是否实际block碰撞器与block碰撞

                    _Chunk::Key ck;
                    _Chunk::Key::getKeyOfPoint(ck, curX, curY, curZ);
                    // App::gamePtr-
                    auto chunk = App::getInstance().gamePtr->chunkManager->getChunkOfKey(ck);
                    if (chunk)
                    {
                        auto pos = ck.getChunkPosFromWorldPos(curX, curY, curZ);
                        auto blockId = chunk->data[_Chunk::blockPos2blockIndex(pos.x, pos.y, pos.z)];
                        auto &blockInfo = App::getInstance().gamePtr->blockManager->getInfo(blockId);
                        if (blockInfo.isEmptyBlock())
                        {
                            //  2.1空气方块，不碰撞，下一个
                            continue;
                        }
                        else
                        {
                            //  2.2非空，需要进行具体的碰撞测试
                            //Vertices vetices;
                            std::vector<Type::Vec3F> vertexPoses;
                            _Graph::Indices indices;
                            blockInfo.blockMesh->getBlockValidTriangles(vertexPoses, indices);
                        }
                    }

                    //4.若碰撞。返回
                    //  若未碰撞。讲curX curY curZ 设置为2步骤中检测的到的碰撞方块
                }
            }
        }
    }
}