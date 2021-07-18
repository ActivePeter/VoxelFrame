class Base_BlockUVSetter;
#pragma once
#include "../enum.h"
#include "game/block.h"
#include "graph/Mesh.h"
#include "app.h"

/////////////////////////////////////////

class Base_BlockUVSetter
{
public:
    void setFaceUVsByTextureIndex(Mesh &mesh, int textureIndex);
    virtual void setVertexUVOnDir(Block_FaceDirection dir, Mesh &mesh) {}
};