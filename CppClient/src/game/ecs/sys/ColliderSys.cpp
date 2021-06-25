#include "ColliderSys.h"

namespace EcsSys
{
    void checkCapsuleCollider2aroundChunkData(
        EcsComp::CapsuleCollider &collider,
        EcsComp::Position3D &pos,
        EcsComp::ChunkRelated &chunks)
    {

        /**
         * 通过chunkrelated可以访问到周围区块的指针
         * 通过pos可以访问到周围方块的数据
         * 通过collider可以跟周围方块进行碰撞
        */
        printf_s("checkCapsuleCollider2aroundChunkData\r\n");
        printf_s("%f %f %f\r\n", pos.x, pos.y, pos.z);
    }
}