#pragma once
#include <reactphysics3d/reactphysics3d.h>

namespace physic_engine
{
    rp3d::PhysicsCommon &physicCommon();
    rp3d::PhysicsWorld &physicWorld();
    rp3d::CapsuleShape &getCapsule(float r, float h);
    rp3d::Transform Transform_normal()
    {
        return rp3d::Transform(
            rp3d::Vector3(0, 0, 0),
            rp3d::Quaternion::identity());
    }
}