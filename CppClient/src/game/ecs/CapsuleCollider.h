#pragma once
#include <reactphysics3d/reactphysics3d.h>
/**
 * 胶囊碰撞器
*/
namespace _EcsComp
{
    struct CapsuleCollider
    {
        rp3d::RigidBody *body;
        // //胶囊端半径
        // float radius;
        // //胶囊高度
        // float height;
        CapsuleCollider(rp3d::RigidBody *body) : body(body) {}
    };

}
