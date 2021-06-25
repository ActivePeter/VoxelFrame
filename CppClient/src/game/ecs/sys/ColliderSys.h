#pragma once
#include "../CapsuleCollider.h"
#include "../VectorAbout.h"
#include "../ChunkRelated.h"
#include "base.h"
namespace EcsSys
{
    /**
     * get check collider for entities in
    */
    void checkCapsuleCollider2aroundChunkData(
        EcsComp::CapsuleCollider &collider,
        EcsComp::Position3D &pos,
        EcsComp::ChunkRelated &chunks);
}