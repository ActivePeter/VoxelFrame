#include "../block.h"

// 不同种类的网格信息，表达在不同文件里，比较清晰
void BlockMesh_Common::setFaceVertexPosOnDir(Vertices &vertices, Block_FaceDirection dir)
{
    // 8个点 对应8个索引
    switch (dir)
    {
    case Block_FaceDirection::X_Positive:
        // 1 4 7 6
        setFaceVertices(vertices, 1, 4, 7, 6);
        break;
    case Block_FaceDirection::X_Negative:
        // 3 5 2 0
        setFaceVertices(vertices, 3, 5, 2, 0);
        break;
    case Block_FaceDirection::Y_Positive:
        // 2 5 7 4
        setFaceVertices(vertices, 2, 5, 7, 4);
        break;
    case Block_FaceDirection::Y_Negative:
        // 1 6 3 0
        setFaceVertices(vertices, 1, 6, 3, 0);
        break;
    case Block_FaceDirection::Z_Positive:
        // 6 7 5 3
        setFaceVertices(vertices, 6, 7, 5, 3);
        break;
    case Block_FaceDirection::Z_Negative:
        // 0 2 4 1
        setFaceVertices(vertices, 0, 2, 4, 1);
        break;

    default:
        std::cout << "no face enum matched" << std::endl;
        break;
    }
}

/**
 * 将方块的相对顶点坐标加到未初始化的顶点上
*/
void BlockMesh_Common::addUpStandardVertexOfIndex(Vertex &vertex, uint8_t index)
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

void BlockMesh_Common::getBlockValidVertices(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) 
{
    
}
