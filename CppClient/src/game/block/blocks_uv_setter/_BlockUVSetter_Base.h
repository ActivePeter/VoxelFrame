class BlockUVSetter_Base;
#pragma once
// #include "../enum.h"
#include "../block.h"
#include "graph/Mesh.h"
#include "app.h"

/////////////////////////////////////////

class BlockUVSetter_Base
{
public:
    void setFaceUVsByTextureIndex(Mesh &mesh, int textureIndex);
    virtual void setVertexUVOnDir(Block_FaceDirection dir, Mesh &mesh) {}
};