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
