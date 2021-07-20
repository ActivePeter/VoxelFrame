#include "block.h"
#include "app.h"

// void CommonBlockMesh::setFaceUVsByTextureIndex(Mesh &mesh, int textureIndex)
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

//注册所有方块
BlockManager::BlockManager()
{
    registerBlockAll(*this);
    // CommonBlockMeshs.resize(255);
}

namespace _Block
{
    void pushOneFace2Mesh(int blockx, int blocky, int blockz, BlockInfo &blockInfo, Block_FaceDirection dir, Mesh &mesh)
    {
        // printf("dir: %d \r\n", dir);
        //Vertex vertex;
        //添加方块坐标和区块坐标（网格坐标）的偏移
        //vertex.setPosition(mesh.mesh_position.x + blockx,
        //mesh.mesh_position.y + blocky,
        //mesh.mesh_position.z + blockz);
        //加入序列
        //for (int i = 0; i < 4; i++)
        //{
        //mesh.vertices.push_back(vertex);
        //}
        //这一块要为了后续程序统一做出整改
        // 构造网格时传入一个空vector<VertexPos>（临时
        // 构造过程中往vector填入内容，
        // 最后构造结束后再把数据拷贝到vertex数组里
        VertexPoses poses;
        blockInfo.blockMesh->pushOneFaceVerticesAndIndices_selfPos(dir, poses, mesh.indices, mesh.vertices.size());
        //加上网格以及方块的坐标，转换到世界坐标上
        for (auto &i : poses)
        {
            i += VertexPos(
                mesh.mesh_position.x + blockx,
                mesh.mesh_position.y + blocky,
                mesh.mesh_position.z + blockz);
        }
        mesh.appendVetexPoses(poses);
        // this->setVertexUVOnDir(dir, mesh);
        blockInfo.blockUVSetter->setVertexUVOnDir(dir, mesh);

        // printf("%d %d\r\n", mesh.vertices.size(), mesh.indices.size());
    }
}