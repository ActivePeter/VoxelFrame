#include "raycast.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace Physics
        {
            static bool raycast2Triangle(
                const Type::Vec3F &startPoint,
                const Type::Vec3F &direction, const Type::Vec3F &triP1, const Type::Vec3F &triP2, const Type::Vec3F &triP3,
                Type::Vec3F &return_cross)
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
                Type::Vec3F k1k2k3 = glm::inverse(p2tvs) * direction;
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
                bool hasColid = false;
                // Type::Vec3F mostCloseP;
                //遍历所有三角形,以找出最近的碰撞点
                for (size_t i = 0; i < indices.size() / 3; i += 3)
                {
                    // Type::Vec3F triangle[3];
                    assert(
                        indices[i] < vertexPoses.size() &&
                        indices[i + 1] < vertexPoses.size() &&
                        indices[i + 2] < vertexPoses.size());
                    // if(indices[i]<vertexPoses.size()&&)
                    Type::Vec3F colidP;
                    bool colid = raycast2Triangle(
                        startPoint, direction,
                        vertexPoses[indices[i]],
                        vertexPoses[indices[i + 1]],
                        vertexPoses[indices[i + 2]],
                        colidP);
                    //之前没有碰撞
                    if (!hasColid && colid)
                    {
                        return_colidPoint = colidP;
                    }
                    else
                    {
                        //跟之前的碰撞点距离比较大小，距离小的作为返回量
                        auto d1 = _Calc::vec3Len(colidP - startPoint);
                        auto d2 = _Calc::vec3Len(return_colidPoint);
                        if (d1 < d2)
                        {
                            return_colidPoint = colidP;
                        }
                    }
                    if (colid)
                    {
                        hasColid = true;
                    }
                }
                return hasColid;
            }
            static bool raycast2ChunkAndReturnBlock(
                const Type::Vec3F &startPoint,
                const Type::Vec3F &direction,
                float maxRange,
                std::shared_ptr<_Chunk::Chunk> &return_chunkPtr,
                int &return_blockIndexInChunk)
            {
                Type::Vec3F delta = direction / VF::_Calc::vec3Len(direction) * maxRange;
                Type::Vec3F endPointF = startPoint + delta;

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

                    //判断是否超出范围
                    if (_Calc::vec3Len(Type::Vec3F(curX, curY, curZ) - startPoint) > maxRange)
                    {
                        return false;
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

                            std::vector<Type::Vec3F> vertexPoses;                              //接收方块所有顶点
                            _Graph::Indices indices;                                           //接受方块所有顶点序号
                            blockInfo.blockMesh->getBlockValidTriangles(vertexPoses, indices); //获取方块三角形

                            Type::Vec3F colidP;
                            bool hasColid = raycast2TrianglesNearest(
                                //射线起点和方向是来自player的cam的，当然这里是参数传进来的
                                startPoint,
                                direction,
                                vertexPoses,
                                indices,
                                colidP);

                            if (hasColid)
                            {
                                return_blockIndexInChunk = _Chunk::blockPos2blockIndex(pos.x, pos.y, pos.z);
                                return_chunkPtr = chunk;
                                return true;
                            }
                        }
                    }
                    else
                    { //没有区块，直接停止
                        return false;
                    }

                    //4.若碰撞。返回
                    //  若未碰撞。讲curX curY curZ 设置为2步骤中检测的到的碰撞方块
                }
            }
        }
    }
}