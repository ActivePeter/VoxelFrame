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
        glm::vec3 delta = direction / VF::vec3Len(direction) * maxRange;
        glm::vec3 endPointF = startPoint + delta;

        int endX = floor(endPointF.x);
        int endY = floor(endPointF.y);
        int endZ = floor(endPointF.z);

        int curX = floor(startPoint.x);
        int curY = floor(startPoint.y);
        int curZ = floor(startPoint.z);

        char dirX = 0, dirY = 0, dirZ = 0;

        dirX = endX > curX ? 1 : dirX;
        dirY = endY > curY ? 1 : dirY;
        dirZ = endZ > curZ ? 1 : dirZ;

        // dirX = endX < curX ? -1 : dirX;
        // dirY = endY < curY ? -1 : dirY;
        // dirZ = endZ < curZ ? -1 : dirZ;
        //未扫描到底，
        while (curX != endX || curY != endY || curZ != endZ)
        {
            //1.找到最先经过的方块
            //  x+1
            float borderX = curX + dirX;
            float borderY = curY + dirY;
            float borderZ = curZ + dirZ;

            float scaleX = (borderX - startPoint.x) / delta.x;
            float scaleY = (borderY - startPoint.y) / delta.y;
            float scaleZ = (borderZ - startPoint.z) / delta.z;
            if (scaleZ > scaleX && scaleY > scaleX)
            {
                //scaleX is min
                curX++;
            }
            else if (scaleZ > scaleY)
            {
                //scaleY is min
                curY++;
            }
            else
            {
                //scaleZ is min
                curZ++;
            }

            //2.判断是否实际block碰撞器与block碰撞
            //  2.1目前都是普通方块，所以不为0（空气时），即为碰撞
            //  2.2要考虑的是以后加入其他形状的方块，则需要跟每一个面检测碰撞。然后最近的碰撞点即为碰撞面。
            //4.若碰撞。返回
            //  若未碰撞。讲curX curY curZ 设置为2步骤中检测的到的碰撞方块
        }
    }
} // namespace VoxelFrame
