#include "Physic.h"
#include "physic_engine/physic_engine.h"
#include "math.h"
#include "game/chunk.h"
namespace EcsSys
{
    /**
     * 更新会跟chunk发生碰撞的entity的周围环境的碰撞器
     * EcsComp::CapsuleCollider 
     * EcsComp::ChunkRelatedTag
     * */
    void updateChunkColliderForChunkRelated(
        EcsComp::CapsuleCollider &collider,
        // EcsComp::Position3D &pos,
        EcsComp::ChunkRelatedTag &chunks)
    {
        //1。算出感兴趣的范围，（区块坐标和方块序列
        auto aabb = collider.body->getAABB();
        auto &maxP = aabb.getMax();
        auto &minP = aabb.getMin();
        int maxX = floor(maxP.x);
        int maxY = floor(maxP.y);
        int maxZ = floor(maxP.z);
        int minX = floor(minP.x);
        int minY = floor(minP.y);
        int minZ = floor(minP.z);

        ChunkKey maxChunkKey, minChunkKey;
        ChunkKey::getChunkKeyOfPoint(maxChunkKey, maxX, maxY, maxZ);
        ChunkKey::getChunkKeyOfPoint(minChunkKey, minX, minY, minZ);
        // ChunkKey()

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
    // void transformWithChunkCollider(const EcsComp::Position3D &posBak,
    //                                 EcsComp::Position3D &oldPos,
    //                                 EcsComp::CapsuleCollider &collider,
    //                                 EcsComp::ChunkRelated &chunks)
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
    //     EcsComp::CapsuleCollider &collider,
    //     EcsComp::Position3D &pos,
    //     EcsComp::ChunkRelated &chunks)
    // // EcsComp::CapsuleCollider *collider,
    // // EcsComp::Position3D *pos,
    // // EcsComp::ChunkRelated *chunks)
    // {
    //     //copy bak
    //     EcsComp::Position3D posBak = pos;
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