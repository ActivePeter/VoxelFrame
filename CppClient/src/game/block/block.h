class BlockManager;
class CommonBlockMesh;

#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "vf_base.h"


#include "blocks_detailed/blocks_registry.h"
#include "graph/Mesh.h"

#include "enum.h"
#include "physic_engine/physic_engine.h"

// #pragma once

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
enum class Block_FaceDirection
    {
        X_Positive = 0,
        X_Negative = 1,
        Y_Positive = 2,
        Y_Negative = 3,
        Z_Positive = 4,
        Z_Negative = 5,
    };
///////////////////////////
class BlockManager;
/**
 * 即最普通的方块状态，撑满一格
*/
#include "blocks_mesh/common_block_mesh.h"
#include "blocks_uv_setter/base_blocks_uv_setter.h"

class BlockInfo{
    Base_BlockUVSetter *block
}

class BlockManager
{
private:
    /**
     * 以方块id的顺序存储方块信息，可以快速的随机访问
    */
    std::vector<CommonBlockMesh> CommonBlockMeshs;

public:
    /**
     * block manager构造函数
    */
    BlockManager();

    /**
     * 添加block信息（在注册block时调用
    */
    void addBlock(const CommonBlockMesh &block)
    {
        CommonBlockMeshs.push_back(block);
    }

    /**
     * 添加一个emptyblock（在注册block时调用
    */
    void addEmptyBlock(const CommonBlockMesh &block)
    {
        // block.isEmptyBlockFlag = false;
        CommonBlockMeshs.push_back(block);
        CommonBlockMeshs.end()->isEmptyBlockFlag = true;
    }
    /**
     * 根据blockId获取blockInfo
    */
    CommonBlockMesh &getBlockInfo(int blockId)
    {
        return CommonBlockMeshs[blockId - 1];
    }
};

#endif // __BLOCK_H__