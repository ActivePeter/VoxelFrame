class BlockManager;
class CommonBlockInfo;

#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "vf_base.h"
#include "blocks_uv_setter/base_blocks_uv_setter.h"

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

//代表最普通的方块状态。

///////////////////////////
class CommonBlockInfo
{
protected:
    //VAR
    bool isEmpty;
    std::shared_ptr<Base_BlockUVSetter> blockUVSetter;

    //FUNC
    inline void setFaceVertices(vector<Vertex> &vertices, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3)
    {
        addUpStandardVertexOfIndex(vertices[vertices.size() - 4], _0);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 3], _1);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 2], _2);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 1], _3);
    }
    /* data */
    // void setFaceUVsByTextureIndex(
    //     Mesh &mesh, int textureIndex);

    /**************************************
     * 方块基础信息3
     * 这个函数包含方块 顶点相对坐标 和 对应的index
     * 参考markdown文件夹里的 方块顶点顺序.md
     * ***************************************/
    void addUpStandardVertexOfIndex(Vertex &vertex, uint8_t index);

public:
    CommonBlockInfo(bool isEmptyBlock)
    {
        // blockUVSetter = blockUVSetter1;
        isEmpty = isEmptyBlock;
    }
    CommonBlockInfo(std::shared_ptr<Base_BlockUVSetter> blockUVSetter1, bool isEmptyBlock)
    {
        blockUVSetter = blockUVSetter1;
        isEmpty = isEmptyBlock;
    }
    /**************************************
     * 方块基础信息1,判断某个方向是否有标准类型面
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
    bool hasStandardFace(BlockAbout::FaceDirection dir)
    {
        return true;
    }

    /**************************************
     * 方块基础信息2
     * 这个函数包含方块每个面的顶点坐标顺序
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
    void setFaceVertexPosOnDir(Mesh &mesh, BlockAbout::FaceDirection dir);
    // virtual void setVertexUVOnDir(BlockAbout::FaceDirection dir, Mesh &mesh) {}
    /**************************************
     * 往区块网格添加一个方块面的函数
     * 包含了三角形的顺序信息（indices
     * ***************************************/
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, BlockAbout::FaceDirection dir, Mesh &mesh);
    //判断是否为空方快（空气类方块
    bool isEmptyBlock()
    {
        return isEmpty;
    }
    rp3d::BoxShape *getBlockColliderShape()
    {
        static rp3d::BoxShape *boxShape;
        if (!boxShape)
        {
            boxShape = physic_engine::physicCommon().createBoxShape(rp3d::Vector3(0.5, 0.5, 0.5));
        }
        return boxShape;
    }
};
class BlockManager
{
private:
    //通过方块id查询方块面状态
    std::vector<CommonBlockInfo> commonBlockInfos;

public:
    // CommonBlockFaceState commonBlockFaceState[];
    BlockManager();
    void addBlock(const CommonBlockInfo &block)
    {
        commonBlockInfos.push_back(block);
    }
    //通过方块id获取方块信息
    CommonBlockInfo &getBlockInfo(int blockId)
    {
        return commonBlockInfos[blockId];
    }
    //尝试通过方块的坐标获取方块信息,如果返沪null。说明没有获取到方块。
    CommonBlockInfo *getBlcokInfoByBlockPos(int bx, int by, int bz);
};

#endif // __BLOCK_H__