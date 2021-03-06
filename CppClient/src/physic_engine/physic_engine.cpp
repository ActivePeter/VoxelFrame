#include "physic_engine.h"
namespace physic_engine
{
    reactphysics3d::PhysicsCommon &physicCommon()
    {
        static reactphysics3d::PhysicsCommon physicCommon;
        return physicCommon;
    }
    reactphysics3d::PhysicsWorld &physicWorld()
    {
        static reactphysics3d::PhysicsWorld *ptr;
        if (!ptr)
        {
            ptr = physicCommon().createPhysicsWorld();
        }
        return *ptr;
    }
    reactphysics3d::CapsuleShape &getCapsule(float r, float h)
    {
        static reactphysics3d::CapsuleShape *ptr;
        if (!ptr)
        {
            ptr = physicCommon().createCapsuleShape(r, h);
        }
        ptr->setRadius(r);
        ptr->setHeight(h);
        return *ptr;
    }

    rp3d::Transform Transform_normal()
    {
        {
            return rp3d::Transform(
                rp3d::Vector3(0, 0, 0),
                rp3d::Quaternion::identity());
        }
    }
}