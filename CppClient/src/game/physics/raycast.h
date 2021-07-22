#pragma once
#include <glm/glm.hpp>
#include "base/vf_base.h"
#include "game/chunk/chunk.h"
#include "app.h"
// #include "math.h"
// #include "tool/calc.h"
#include "numeric"
// #include "main_player.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace Physics
        {
            //推导过程 见 ./markdown/record.md 7.14
            static bool raycast2Triangle(
                const glm::vec3 &startPoint,
                const glm::vec3 &direction, const glm::vec3 &triP1, const glm::vec3 &triP2, const glm::vec3 &triP3,
                glm::vec3 &return_cross);

            static void raycast2TrianglesNearest(const glm::vec3 &startPoint, const glm::vec3 &direction);

            /**
             * 射线检测是否碰到方块，
             *      若碰到方块，返回方块所在区块的指针以及方块的序号，
             *      若没碰到，指针为空
            */
            static void raycast2ChunkAndReturnBlock(
                const glm::vec3 &startPoint,
                const glm::vec3 &direction,
                float maxRange,
                std::vector<_Chunk::Chunk> &return_chunkPtr,
                int &return_blockIndexInChunk);

            // #include "raycast.declare.h"
        }
    }

} // namespace VoxelFrame
