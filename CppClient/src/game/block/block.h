class BlockManager;
class CommonBlockMesh;

#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "vf_base.h"

#include "blocks_registry.h"
#include "graph/Mesh.h"

// #include "enum.h"
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
#include "blocks_mesh/_BlockMesh_Base.h"

#include "blocks_uv_setter/_BlockUVSetter_Base.h"

/**
    存储所有方块信息，
    若empty，则uvsetter和blockmesh是没有的
*/
struct BlockInfo
{
    std::shared_ptr<BlockUVSetter_Base> blockUVSetter;
    std::shared_ptr<BlockMesh_Base> blockMesh;
    bool isEmptyBlockFlag = false;

    /**
     * 判断是否为空方快
    */
    bool isEmptyBlock()
    {
        return isEmptyBlockFlag;
    }
    static BlockInfo newEmptyBlock()
    {
        BlockInfo blockInfo;
        blockInfo.isEmptyBlockFlag = true;
        return blockInfo;
    }
    /*
        模板构造函数
    */
    template <typename BlockUVSetterType, typename BlockMeshType>
    BlockInfo(BlockUVSetterType blockUVSetter, BlockMeshType blockMesh)
    {
        this->blockUVSetter = static_cast<BlockUVSetter_Base>(blockUVSetter);
        this->blockMesh = static_cast<BlockMesh_Base>(blockMesh);
    }
}

class BlockManager
{
private:
    /**
     * 以方块id的顺序存储方块信息，可以快速的随机访问
    */
    std::vector<BlockInfo> blockInfos;

public:
    /**
     * block manager构造函数
    */
    BlockManager();

    /**
     * 添加block信息（在注册block时调用
    */
    void addBlock(const BlockInfo &blockInfo)
    {
        blockInfos.push_back(blockInfo);
    }

    /**
     * 添加一个emptyblock（在注册block时调用
    */
    void addEmptyBlock(const BlockInfo &blockInfo)
    {
        blockInfos.push_back(blockInfo);
        //设置为空方块属性
        blockInfos.end()->blockMesh->isEmptyBlockFlag = true;
    }
    /**
     * 根据blockId获取blockInfo
    */
    BlockInfo &getBlockInfo(int blockId)
    {
        return blockInfos[blockId];
    }
};

#endif // __BLOCK_H__