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
    inline void pushIndices(vector<unsigned int> &target, unsigned int _0, unsigned int _1, unsigned int _2, unsigned int _3, unsigned int _4, unsigned int _5)
    {
        target.push_back(_0);
        target.push_back(_1);
        target.push_back(_2);
        target.push_back(_3);
        target.push_back(_4);
        target.push_back(_5);
        // indices[0] = _0;
        // indices[1] = _1;
        // indices[2] = _2;
        // indices[3] = _3;
        // indices[4] = _4;
        // indices[5] = _5;
        // std::cout << "hhh:";
        // for (int i = 0; i < 6; i++)
        // {
        //     std::cout << indices[i] << ",";
        // }
        // std::cout << std::endl;
    }
    inline void setFaceVertices(vector<Vertex> &vertices, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3)
    {
        addUpStandardVertexOfIndex(vertices[vertices.size() - 4], _0);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 3], _1);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 2], _2);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 1], _3);
    }

    //标准方块顶点坐标和索引的对应信息
    void addUpStandardVertexOfIndex(Vertex &vertex, uint8_t index)
    {
        switch (index)
        {
        //need do nothing
        // case 0:
        //     vertex.addPosition(0,0,0);
        //     break;
        case 1:
            vertex.addPosition(1, 0, 0);
            break;
        case 2:
            vertex.addPosition(0, 1, 0);
            break;
        case 3:
            vertex.addPosition(0, 0, 1);
            break;
        case 4:
            vertex.addPosition(1, 1, 0);
            break;
        case 5:
            vertex.addPosition(0, 1, 1);
        case 6:
            vertex.addPosition(1, 0, 1);
            break;
        case 7:
            vertex.addPosition(1, 1, 1);
            break;
        }
    }

public:
    enum FaceDirection
    {
        FaceX_Positive = 0,
        FaceX_Negative = 1,
        FaceY_Positive = 2,
        FaceY_Negative = 3,
        FaceZ_Positive = 4,
        FaceZ_Negative = 5,
    };

    //方块基础信息1,判断某个方向是否有标准类型面
    bool hasStandardFace(FaceDirection dir)
    {
        return true;
    }

    //这个函数包含方块所有顶点坐标信息
    void setFaceVertexPosOnDir(Mesh &mesh, FaceDirection dir)
    {

        // 8个点 对应8个索引
        switch (dir)
        {
        case FaceX_Positive:
            // 1 4 7 6
            setFaceVertices(mesh.vertices, 1, 4, 7, 6);
            break;
        case FaceX_Negative:
            // 3 5 2 0
            setFaceVertices(mesh.vertices, 3, 5, 2, 0);
            break;
        case FaceY_Positive:
            // 2 5 7 4
            setFaceVertices(mesh.vertices, 2, 5, 7, 4);
            break;
        case FaceY_Negative:
            // 1 6 3 0
            setFaceVertices(mesh.vertices, 1, 6, 3, 0);
            break;
        case FaceZ_Positive:
            // 6 7 5 3
            setFaceVertices(mesh.vertices, 6, 7, 5, 3);
            break;
        case FaceZ_Negative:
            // 0 2 4 1
            setFaceVertices(mesh.vertices, 0, 2, 4, 1);
            break;

        default:
            std::cout << "no face enum matched" << std::endl;
            break;
        }
    }
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, FaceDirection dir, Mesh &mesh)
    {
        Vertex vertex;
        vertex.setPosition(blockx, blocky, blockz);
        mesh.expandVertices(vertex, 4);
        setFaceVertexPosOnDir(mesh, dir);
        mesh.indices.push_back(mesh.vertices.size() - 4);
        mesh.indices.push_back(mesh.vertices.size() - 3);
        mesh.indices.push_back(mesh.vertices.size() - 2);
        mesh.indices.push_back(mesh.vertices.size() - 4);
        mesh.indices.push_back(mesh.vertices.size() - 2);
        mesh.indices.push_back(mesh.vertices.size() - 1);
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
