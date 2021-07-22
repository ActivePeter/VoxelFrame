namespace VoxelFrame
{
    namespace _Game
    {
        class BlockUVSetter_Base;
    }
}
#pragma once
// #include "../enum.h"
#include "../block.h"
#include "graph/Mesh.h"
#include "app.h"

/////////////////////////////////////////
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Block
        {
            class BlockUVSetter_Base
            {
            public:
                void setFaceUVsByTextureIndex(_Graph::Mesh &mesh, int textureIndex);
                virtual void setVertexUVOnDir(_Block::FaceDirection dir, _Graph::Mesh &mesh) = 0;
            };
        }
    }
}