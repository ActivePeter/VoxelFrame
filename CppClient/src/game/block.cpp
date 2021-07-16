#include "block.h"
#include "app.h"

// void CommonBlockInfo::setFaceUVsByTextureIndex(Mesh &mesh, int textureIndex)
// {
//     float uvs[8];
//     auto size = mesh.vertices.size();
//     auto &tm = *App::getInstance().graphPtr->_textureManagerPtr;
//     tm.getBlockFaceUVsByTextureIndex(uvs, textureIndex);
//     mesh.vertices[size - 4].setUV(uvs[0], uvs[1]);
//     mesh.vertices[size - 3].setUV(uvs[2], uvs[3]);
//     mesh.vertices[size - 2].setUV(uvs[4], uvs[5]);
//     mesh.vertices[size - 1].setUV(uvs[6], uvs[7]);
// }

void CommonBlockInfo::pushOneFace2Mesh(int blockx, int blocky, int blockz, BlockAbout::FaceDirection dir, Mesh &mesh)
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
        setFaceVertexPosOnDir(mesh, dir);

        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 4));
        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 3));
        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 2));
        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 4));
        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 2));
        mesh.indices.push_back((unsigned int)(mesh.vertices.size() - 1));
        // this->setVertexUVOnDir(dir, mesh);
        blockUVSetter->setVertexUVOnDir(dir, mesh);

        // printf("%d %d\r\n", mesh.vertices.size(), mesh.indices.size());
    }
}

void CommonBlockInfo::pushOneFaceVerticesAndIndices_selfPos(BlockAbout::FaceDirection dir,
                                                            std::vector<Vertex> &vertices,
                                                            std::vector<unsigned int> &indices)
{
}

//注册所有方块
BlockManager::BlockManager()
{
    registerBlockAll(*this);
    // commonBlockInfos.resize(255);
}
