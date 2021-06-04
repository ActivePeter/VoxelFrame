#pragma once
#include "base.h"
// class CommonBlockMeshModel
// {
// private:
//     int []
//     /* data */
// public:
// };

//标准顺序

// uint32_t _0_0_0 = getIndexByPos(x + 0, y + 0, z + 0);
// uint32_t _1_0_0 = getIndexByPos(x + 1, y + 0, z + 0);
// uint32_t _0_1_0 = getIndexByPos(x + 0, y + 1, z + 0);
// uint32_t _0_0_1 = getIndexByPos(x + 0, y + 0, z + 1);
// uint32_t _1_1_0 = getIndexByPos(x + 1, y + 1, z + 0);
// uint32_t _0_1_1 = getIndexByPos(x + 0, y + 1, z + 1);
// uint32_t _1_0_1 = getIndexByPos(x + 1, y + 0, z + 1);
// uint32_t _1_1_1 = getIndexByPos(x + 1, y + 1, z + 1);
//

//代表最普通的方块状态。
class CommonBlockInfo
{
private:
    inline void setIndices(uint8_t (&indices)[6], uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5)
    {
        indices[0] = _0;
        indices[1] = _1;
        indices[2] = _2;
        indices[3] = _3;
        indices[4] = _4;
        indices[5] = _5;
    }

public:
    enum FaceDirection
    {
        FaceX_Positive,
        FaceX_Negative,
        FaceY_Positive,
        FaceY_Negative,
        FaceZ_Positive,
        FaceZ_Negative,
    };
    bool hasFace(FaceDirection dir)
    {
        return true;
    }
    //逆时针为正面
    void getFaceIndices(FaceDirection dir, uint8_t (&indices)[6])
    {
        switch (dir)
        {
        case FaceX_Positive:
            setIndices(indices, 1, 6, 4, 4, 6, 7);
            break;
        case FaceX_Negative:
            setIndices(indices, 3, 0, 2, 2, 5, 3);
            break;
        case FaceY_Positive:
            setIndices(indices, 2, 4, 7, 7, 5, 2);
            break;
        case FaceY_Negative:
            setIndices(indices, 0, 3, 6, 6, 1, 0);
            break;
        case FaceZ_Positive:
            setIndices(indices, 3, 5, 7, 7, 6, 3);
            break;
        case FaceZ_Negative:
            setIndices(indices, 0, 1, 4, 4, 2, 0);
            break;

        default:
            break;
        }
    }
};
class BlockManager
{
private:
    //通过方块id查询方块面状态
    std::vector<CommonBlockInfo> commonBlockInfos;

public:
    // CommonBlockFaceState commonBlockFaceState[];
    BlockManager()
    {
        commonBlockInfos.resize(255);
    }
    CommonBlockInfo &getBlockInfo(int blockId)
    {
        return commonBlockInfos[blockId];
    }
};
