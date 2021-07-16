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
class BlockManager;
class CommonBlockInfo
{
    friend class BlockManager;

protected:
    /**
     * 根据四个序号 初始化（获取到vertices里）一面的顶点坐标
    */
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
    bool isEmptyBlockFlag = false;

public:
    std::shared_ptr<Base_BlockUVSetter> blockUVSetter;

    /**
     * 空的blockInfo的构造函数
    */
    CommonBlockInfo() {}

    /**
     * 普通的（有uv材质的）blockInfo的构造函数， 
    */
    CommonBlockInfo(std::shared_ptr<Base_BlockUVSetter> blockUVSetter1)
    {
        blockUVSetter = blockUVSetter1;
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
     * 顶点信息（vertices
     * 材质信息（uv
     * 
     * 网格是区块网格，所以要加上方块的坐标作为顶点的偏移
     * ***************************************/
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, BlockAbout::FaceDirection dir, Mesh &mesh);

    /**
     * 获取某一面的顶点信息到序列里
     *  （相对方块自身的坐标
    */
    void pushOneFaceVerticesAndIndices_selfPos(
        BlockAbout::FaceDirection dir,
        std::vector<Vertex> &vertices,
        std::vector<unsigned int> &indices);

    /**
     * 获取方块的物理碰撞器形状
    */
    rp3d::BoxShape *getBlockColliderShape()
    {
        static rp3d::BoxShape *boxShape;
        if (!boxShape)
        {
            boxShape = physic_engine::physicCommon().createBoxShape(rp3d::Vector3(0.5, 0.5, 0.5));
        }
        return boxShape;
    }
    /**
     * 判断是否为空方快
    */
    bool isEmptyBlock()
    {
        return isEmptyBlockFlag;
    }
    /**
     * 获取方块所有的网格三角形(以vertex序列和index序列表示)
    */
    void getBlockValidVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    {
    }
};

class BlockManager
{
private:
    /**
     * 以方块id的顺序存储方块信息，可以快速的随机访问
    */
    std::vector<CommonBlockInfo> commonBlockInfos;

public:
    /**
     * block manager构造函数
    */
    BlockManager();

    /**
     * 添加block信息（在注册block时调用
    */
    void addBlock(const CommonBlockInfo &block)
    {
        commonBlockInfos.push_back(block);
    }

    /**
     * 添加一个emptyblock（在注册block时调用
    */
    void addEmptyBlock(const CommonBlockInfo &block)
    {
        // block.isEmptyBlockFlag = false;
        commonBlockInfos.push_back(block);
        commonBlockInfos.end()->isEmptyBlockFlag = true;
    }
    /**
     * 根据blockId获取blockInfo
    */
    CommonBlockInfo &getBlockInfo(int blockId)
    {
        return commonBlockInfos[blockId - 1];
    }
};

#endif // __BLOCK_H__