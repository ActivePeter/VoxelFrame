#pragma once
#include "vf_base.h"
class CommonBlockMesh
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
    CommonBlockMesh() {}

    /**
     * 普通的（有uv材质的）blockInfo的构造函数， 
    */
    CommonBlockMesh(std::shared_ptr<Base_BlockUVSetter> blockUVSetter1)
    {
        blockUVSetter = blockUVSetter1;
    }
    /**************************************
     * 方块基础信息1,判断某个方向是否有标准类型面
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
    bool hasStandardFace(Block_FaceDirection dir)
    {
        return true;
    }

    /**************************************
     * 方块基础信息2
     * 这个函数包含方块每个面的顶点坐标顺序
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
    void setFaceVertexPosOnDir(Vertices &vertices, Block_FaceDirection dir);
    // virtual void setVertexUVOnDir(Block_FaceDirection dir, Mesh &mesh) {}

    /**************************************
     * 往区块网格添加一个方块面的函数
     * 包含了三角形的顺序信息（indices
     * 顶点信息（vertices
     * 材质信息（uv
     * 
     * 网格是区块网格，所以要加上方块的坐标作为顶点的偏移
     * ***************************************/
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, Block_FaceDirection dir, Mesh &mesh);

    /**
     * 获取某一面的顶点信息到序列里
     *  （相对方块自身的坐标
    */
    void pushOneFaceVerticesAndIndices_selfPos(
        Block_FaceDirection dir,
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
    void getBlockValidVertices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
    {
    }
};