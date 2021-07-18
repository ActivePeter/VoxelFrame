#pragma once
#include "physic_engine/physic_engine.h"
#include "../block.h"
class BlockMesh_Base
{
    friend class BlockManager;

public:
    virtual rp3d::BoxShape *getBlockColliderShape() = 0;

    /**
     * 获取方块所有的网格三角形(以vertex序列和index序列表示)
    */
    virtual void getBlockValidVertices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};