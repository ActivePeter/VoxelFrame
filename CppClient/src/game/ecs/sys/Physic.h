#pragma once
#include "../CapsuleCollider.h"
#include "../VectorAbout.h"
// #include "../ChunkRelated.h"
#include "../Tags.h"
#include "base/vf_base.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _EcsSys
        {
            void updateChunkColliderForChunkRelated(
                _EcsComp::CapsuleCollider &collider,
                // _EcsComp::Position3D &pos,
                _EcsComp::ChunkRelatedTag &chunks);
            /**
     * get check collider for entities in
    */
            // void gravity(
            //     _EcsComp::CapsuleCollider &collider,
            //     _EcsComp::Position3D &pos,
            //     _EcsComp::ChunkRelated &chunks);
        }
    }
}