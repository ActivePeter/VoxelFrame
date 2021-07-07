#pragma once
#include "physic_engine/physic_engine.h"
class Rigid
{
private:
    rp3d::RigidBody *rigidBody;
    /* data */
public:
    Rigid(/* args */)
    {
        //创建物理刚体
        rigidBody = physic_engine::physicWorld().createRigidBody(physic_engine::Transform_normal());
    }
    ~Rigid()
    {
        physic_engine::physicWorld().destroyRigidBody(rigidBody);
    }
    rp3d::RigidBody &getRigid()
    {
        return *rigidBody;
    }
};