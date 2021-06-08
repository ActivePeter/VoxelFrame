#pragma once
#include "game/block.h"
#include "graph/Mesh.h"
#include "app.h"

//还可以在实例化的时候自动将自己的材质预先加入到要构建的材质列表中，并且记录自己的材质对应的索引
// 最后所有block加载完
// 进行材质合并

class GrassBlockInfo : public CommonBlockInfo
{
private:
    //需要有一个在材质中的位置
    //因为所有方块会被拼到一个材质里
    //index
    int topIndex;
    int sideIndex;
    int bottomIndex;

public:
    void registTexture()
    {
        auto &textureManager = *(App::getInstance().graphPtr->_textureManagerPtr);
        topIndex = textureManager.registBlockFaceTexture("grass_top");
        sideIndex = textureManager.registBlockFaceTexture("grass_side");
        bottomIndex = textureManager.registBlockFaceTexture("grass_bottom");
    }
    void setVertexUVOnDir(FaceDirection dir, Mesh &mesh)
    {
        auto size = mesh.vertices.size();
        switch (dir)
        {
        case FaceX_Positive: //侧面
        case FaceX_Negative:
        case FaceZ_Negative:
        case FaceZ_Positive:
            setFaceUVsByTextureIndex(mesh, sideIndex);
            //根据index 还有材质的总数，就可以算出材质具体的位置，然后对应顶点进行配置即可
            /* code */
            break;
        case FaceY_Negative: //底面
            setFaceUVsByTextureIndex(mesh, bottomIndex);
            break;
        case FaceY_Positive: //上面
            setFaceUVsByTextureIndex(mesh, topIndex);
            break;
        }
    }
};
