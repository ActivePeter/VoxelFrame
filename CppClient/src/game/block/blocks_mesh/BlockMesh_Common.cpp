#include "BlockMesh_Common.h"

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


void BlockMesh_Common::addUpStandardVertexOfIndex(VertexPos &vertexPos, uint8_t index)
{
    switch (index)
    {
    // case 0: nothing need to do 
    //     vertex.addPosition(0,0,0);
    //     break;
    case 1:
        vertexPos+= VertexPos(1,0,0);
        //vertex.addPosition(1, 0, 0);
        break;
    case 2:
        //vertex.addPosition(
        vertexPos += VertexPos(0, 1, 0);
        
        break;
    case 3:
        //vertex.addPosition(
        vertexPos += VertexPos(0, 0, 1);
        break;
    case 4:
        //vertex.addPosition(
        vertexPos += VertexPos(1, 1, 0);
        break;
    case 5:
        //vertex.addPosition(
        vertexPos += VertexPos(0, 1, 1);
        break;
    case 6:
        //vertex.addPosition(
        vertexPos += VertexPos(1, 0, 1);
        break;
    case 7:
        //vertex.addPosition(
        vertexPos += VertexPos(1, 1, 1);
        break;
    }
}

void BlockMesh_Common::getBlockValidTriangles(std::vector<VertexPos>& verticesPos, std::vector<unsigned int>& indices)
{
    Vertex vertex;
    //添加方块坐标和区块坐标（网格坐标）的偏移
    //vertex.setPosition();
    //加入序列
    for (int i = 0; i < 4; i++)
    {
        mesh.vertices.push_back(vertex);
    }
}
void BlockMesh_Common::pushOneFace2Mesh(int blockx, int blocky, int blockz, Block_FaceDirection dir, Mesh& mesh)
{
    {
        // printf("dir: %d \r\n", dir);
        Vertex vertex;
        //添加方块坐标和区块坐标（网格坐标）的偏移
        vertex.setPosition(mesh.mesh_position.x + blockx,
            mesh.mesh_position.y + blocky,
            mesh.mesh_position.z + blockz);
        //加入序列
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(vertex);
        }
        //这一块要为了后续程序统一做出整改
        // 构造网格时传入一个空vector<VertexPos>（临时 
        // 构造过程中往vector填入内容，
        // 最后构造结束后再把数据拷贝到vertex数组里
        this->pushOneFaceVerticesAndIndices_selfPos(dir, mesh.vertices, mesh.indices);
        // this->setVertexUVOnDir(dir, mesh);
        blockUVSetter->setVertexUVOnDir(dir, mesh);

        // printf("%d %d\r\n", mesh.vertices.size(), mesh.indices.size());
    }
}

void BlockMesh_Common::pushOneFaceVerticesAndIndices_selfPos(Block_FaceDirection dir,
    std::vector<Vertex>& vertices,
    std::vector<unsigned int>& indices)
{
    setFaceVertexPosOnDir(vertices, dir);
    //三角形点序号，对应刚添加的四个点
    indices.push_back((unsigned int)(vertices.size() - 4));
    indices.push_back((unsigned int)(vertices.size() - 3));
    indices.push_back((unsigned int)(vertices.size() - 2));
    indices.push_back((unsigned int)(vertices.size() - 4));
    indices.push_back((unsigned int)(vertices.size() - 2));
    indices.push_back((unsigned int)(vertices.size() - 1));
}
