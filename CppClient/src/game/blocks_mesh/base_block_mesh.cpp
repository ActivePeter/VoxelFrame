#include "../block.h"

// 不同种类的网格信息，表达在不同文件里，比较清晰
void CommonBlockInfo::setFaceVertexPosOnDir(Mesh &mesh, BlockAbout::FaceDirection dir)
{
    // 8个点 对应8个索引
    switch (dir)
    {
    case BlockAbout::FaceX_Positive:
        // 1 4 7 6
        setFaceVertices(mesh.vertices, 1, 4, 7, 6);
        break;
    case BlockAbout::FaceX_Negative:
        // 3 5 2 0
        setFaceVertices(mesh.vertices, 3, 5, 2, 0);
        break;
    case BlockAbout::FaceY_Positive:
        // 2 5 7 4
        setFaceVertices(mesh.vertices, 2, 5, 7, 4);
        break;
    case BlockAbout::FaceY_Negative:
        // 1 6 3 0
        setFaceVertices(mesh.vertices, 1, 6, 3, 0);
        break;
    case BlockAbout::FaceZ_Positive:
        // 6 7 5 3
        setFaceVertices(mesh.vertices, 6, 7, 5, 3);
        break;
    case BlockAbout::FaceZ_Negative:
        // 0 2 4 1
        setFaceVertices(mesh.vertices, 0, 2, 4, 1);
        break;

    default:
        std::cout << "no face enum matched" << std::endl;
        break;
    }
}

void CommonBlockInfo::addUpStandardVertexOfIndex(Vertex &vertex, uint8_t index)
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
