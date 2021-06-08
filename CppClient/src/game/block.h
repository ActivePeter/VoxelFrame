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
protected:
    inline void setFaceVertices(vector<Vertex> &vertices, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3)
    {
        addUpStandardVertexOfIndex(vertices[vertices.size() - 4], _0);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 3], _1);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 2], _2);
        addUpStandardVertexOfIndex(vertices[vertices.size() - 1], _3);
    }
    /* data */
    void setFaceUVsByTextureIndex(
        Mesh &mesh, int textureIndex)
    {
        float uvs[8];
        auto size = mesh.vertices.size();
        auto &tm = *App::getInstance().graphPtr->_textureManagerPtr;
        tm.getBlockFaceUVsByTextureIndex(uvs, textureIndex);
        mesh.vertices[size - 4].setUV(uvs[0], uvs[1]);
        mesh.vertices[size - 3].setUV(uvs[2], uvs[3]);
        mesh.vertices[size - 2].setUV(uvs[4], uvs[5]);
        mesh.vertices[size - 1].setUV(uvs[6], uvs[7]);
    }

    /**************************************
     * 方块基础信息3
     * 这个函数包含方块 顶点相对坐标 和 对应的index
     * 参考markdown文件夹里的 方块顶点顺序.md
     * ***************************************/
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
            break;
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

    /**************************************
     * 方块基础信息1,判断某个方向是否有标准类型面
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
    bool hasStandardFace(FaceDirection dir)
    {
        return true;
    }

    /**************************************
     * 方块基础信息2
     * 这个函数包含方块每个面的顶点坐标顺序
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
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
    /**************************************
     * 往区块网格添加一个方块面的函数
     * 包含了三角形的顺序信息（indices
     * ***************************************/
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, FaceDirection dir, Mesh &mesh)
    {
        // printf("dir: %d \r\n", dir);
        Vertex vertex;
        vertex.setPosition(blockx, blocky, blockz);
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(vertex);
        }
        setFaceVertexPosOnDir(mesh, dir);

        mesh.indices.push_back(mesh.vertices.size() - 4);
        mesh.indices.push_back(mesh.vertices.size() - 3);
        mesh.indices.push_back(mesh.vertices.size() - 2);
        mesh.indices.push_back(mesh.vertices.size() - 4);
        mesh.indices.push_back(mesh.vertices.size() - 2);
        mesh.indices.push_back(mesh.vertices.size() - 1);
        // printf("%d %d\r\n", mesh.vertices.size(), mesh.indices.size());
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
