#pragma once
#include <glm/glm.hpp>
#include "vf_base.h"
#include "chunk.h"
#include "app.h"
// #include "math.h"
#include "tool/calc.h"
// #include "main_player.h"
namespace VoxelFrame
{

    /**
     * 射线检测是否碰到方块，
     *      若碰到方块，返回方块所在区块的指针以及方块的序号，
     *      若没碰到，指针为空
    */
    static void raycast2ChunkAndReturnBlock(
        const glm::vec3 &startPoint,
        const glm::vec3 &direction,
        float maxRange,
        std::vector<Chunk> &return_chunkPtr,
        int &return_blockIndexInChunk)
    {
        glm::vec3 endPointF = startPoint +
                              direction / VF::vec3Len(direction) * maxRange;
        int endX = floor(endPointF.x);
        int endY = floor(endPointF.y);
        int endZ = floor(endPointF.z);
    }
} // namespace VoxelFrame
