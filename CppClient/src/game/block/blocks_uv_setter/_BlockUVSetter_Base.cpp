#include "_BlockUVSetter_Base.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Block
        {
            //对应基础类型方块的网格设置uv
            void BlockUVSetter_Base::setFaceUVsByTextureIndex(_Graph::Mesh &mesh, int textureIndex)
            {
                float uvs[8];
                auto size = mesh.vertices.size();
                auto &tm = *App::getInstance().graphPtr->_textureManagerPtr;
                tm.getBlockFaceUVsByTextureIndex(uvs, textureIndex);
                mesh.vertices[size - 4].setUV(uvs[0], uvs[1]);
                mesh.vertices[size - 3].setUV(uvs[2], uvs[3]);
                mesh.vertices[size - 2].setUV(uvs[4], uvs[5]);
                mesh.vertices[size - 1].setUV(uvs[6], uvs[7]);
            }
        }
    }
}