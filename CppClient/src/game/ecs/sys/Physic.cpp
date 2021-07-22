#include "Physic.h"
#include "physic_engine/physic_engine.h"
#include "math.h"
#include "game/chunk/chunk.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _EcsSys
        {
            /**
     * 更新会跟chunk发生碰撞的entity的周围环境的碰撞器
     * _EcsComp::CapsuleCollider 
     * _EcsComp::ChunkRelatedTag
     * */
            void updateChunkColliderForChunkRelated(
                _EcsComp::CapsuleCollider &collider,
                // _EcsComp::Position3D &pos,
                _EcsComp::ChunkRelatedTag &chunks)
            {
                //1。算出感兴趣的范围，（区块坐标和方块序列
                auto aabb = collider.body->getAABB();
                auto &maxP = aabb.getMax();
                auto &minP = aabb.getMin();
                //边界占用方块坐标
                int maxX = floor(maxP.x) + 1;
                int maxY = floor(maxP.y) + 1;
                int maxZ = floor(maxP.z) + 1;
                int minX = floor(minP.x) - 1;
                int minY = floor(minP.y) - 1;
                int minZ = floor(minP.z) - 1;
                _Chunk::Key maxChunkKey, minChunkKey;
                _Chunk::Key::getKeyOfPoint(maxChunkKey, maxX, maxY, maxZ);
                _Chunk::Key::getKeyOfPoint(minChunkKey, minX, minY, minZ);
                // printf_s("chunk_key %d %d %d\r\n", maxChunkKey.x, maxChunkKey.y, maxChunkKey.z);
                for (int cx = minChunkKey.x; cx <= maxChunkKey.x; cx++)
                {
                    int chunkBlockMinX = 0;
                    int chunkBlockMaxX = VF_ChunkWidth - 1;
                    if (cx == minChunkKey.x)
                    {
                        //方块相对区块的坐标
                        chunkBlockMinX = minX - cx * VF_ChunkWidth;
                    }
                    if (cx == maxChunkKey.x)
                    {
                        chunkBlockMaxX = maxX - cx * VF_ChunkWidth;
                    }
                    for (int cy = minChunkKey.y; cy <= maxChunkKey.y; cy++)
                    {
                        int chunkBlockMinY = 0;
                        int chunkBlockMaxY = VF_ChunkWidth - 1;
                        if (cy == minChunkKey.y)
                        {
                            chunkBlockMinY = minY - cy * VF_ChunkWidth;
                        }
                        if (cy == maxChunkKey.y)
                        {
                            chunkBlockMaxY = maxY - cy * VF_ChunkWidth;
                        }
                        for (int cz = minChunkKey.z; cz <= maxChunkKey.z; cz++)
                        {
                            int chunkBlockMinZ = 0;
                            int chunkBlockMaxZ = VF_ChunkWidth - 1;
                            if (cz == minChunkKey.z)
                            {
                                chunkBlockMinZ = minZ - cz * VF_ChunkWidth;
                            }
                            if (cz == maxChunkKey.z)
                            {
                                chunkBlockMaxZ = maxZ - cz * VF_ChunkWidth;
                            }
                            auto chunkPtr = App::getInstance().gamePtr->chunkManager->getChunkOfKey(_Chunk::Key(cx, cy, cz));
                            chunkPtr->setInRangeBlockActive(chunkBlockMinX, chunkBlockMinY, chunkBlockMinZ,
                                                            chunkBlockMaxX, chunkBlockMaxY, chunkBlockMaxZ);
                            //至此以及提取出了方块遍历范围，
                            //遍历区块范围内的感兴趣方块，
                        }
                    }
                }
                // Key()

                //2.根据方块序列设置区块中方块的active状态
                /**
         * 由于得遍历完所有chunkrelated才能确定最终的chunk状态，所以这里只进行active状态的存储。存入一个bitset
         * 然后在这些system执行完之后，遍历一遍bitset，具体设置chunk中rigid的active状态
        */

                //3.之后就可以交给物理系统安心的碰撞了。
            }
            /**
     * 在碰撞器限制下执行移动
    */
            // void transformWithChunkCollider(const _EcsComp::Position3D &posBak,
            //                                 _EcsComp::Position3D &oldPos,
            //                                 _EcsComp::CapsuleCollider &collider,
            //                                 _EcsComp::ChunkRelated &chunks)
            // {

            //     if (!collider.body)
            //     {
            //         //body trans
            //         rp3d::Vector3 position(0, 30, 0);
            //         rp3d::Quaternion orientation = rp3d::Quaternion::identity();
            //         rp3d::Transform transform(position, orientation);
            //         //collider trans

            //         // rp3d::Vector3 position2(, posBak.y, posBak.z);
            //         // rp3d::Quaternion orientation = rp3d::Quaternion::identity();
            //         // rp3d::Transform transform(position, orientation);
            //         collider.body = physic_engine::physicWorld().createRigidBody(transform);
            //         // position.x = 0;
            //         // position.y = 0;
            //         // position.z = 0;
            //         transform.setPosition(rp3d::Vector3(0, 0, 0));
            //         collider.body->setType(rp3d::BodyType::DYNAMIC);
            //         collider.body->addCollider(
            //             &physic_engine::getCapsule(0.4f, 0.8f), transform);
            //         // auto a=physic_engine::physicWorld().createRigidBody(transform);

            //         chunks.body2 = physic_engine::physicWorld().createRigidBody(transform);
            //         chunks.body2->setType(rp3d::BodyType::STATIC);
            //         chunks.body2->addCollider(
            //             physic_engine::physicCommon().createBoxShape(rp3d::Vector3(10, 10, 10)), transform);
            //         // chunks.body2
            //         // a->setType()
            //     }
            //     auto &ori = collider.body->getTransform().getOrientation();
            //     printf_s("capsule %f %f %f", ori.x, ori.y, ori.z);
            //     // physic_engine::physicWorld().testCollision(, )
            //     auto &p = collider.body->getWorldPoint(rp3d::Vector3(0, 0, 0));
            //     oldPos = {p.x, p.y, p.z};
            // }
            // void gravity(
            //     _EcsComp::CapsuleCollider &collider,
            //     _EcsComp::Position3D &pos,
            //     _EcsComp::ChunkRelated &chunks)
            // // _EcsComp::CapsuleCollider *collider,
            // // _EcsComp::Position3D *pos,
            // // _EcsComp::ChunkRelated *chunks)
            // {
            //     //copy bak
            //     _EcsComp::Position3D posBak = pos;
            //     posBak.y -= 0.01f;
            //     transformWithChunkCollider(posBak, pos, collider, chunks);
            //     // pos->y -= 0.01f;
            //     // pos.y -= 0.01f;
            //     /**
            //      * 通过chunkrelated可以访问到周围区块内的方块信息
            //      * 通过pos可以访问到周围方块的数据
            //      * 通过collider可以访问到collider信息
            //      * 通过
            //     */
            //     printf_s("gravity\r\n");
            //     // printf_s("%f %f %f\r\n", pos.x, pos.y, pos.z);
            // }
        }
    }

}