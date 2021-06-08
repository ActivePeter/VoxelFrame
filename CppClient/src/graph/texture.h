#pragma once
#include "base.h"
//负责接收注册和构建贴图
class TextureManager
{
private:
    //合并后的材质宽度上方块数量
    int blocksMixedTextureW = 1;
    float perBlockTextureWidth = 1; //需要在最后变为  1/ blocksMixedTextureW; //单个材质的uv宽度
    /* data */
public:
    /**
     * 注册方块一面的贴图
     * **/
    int registBlockFaceTexture(std::string TextureFileName)
    {
    }
    void registBlockFacesEnd()
    {
        perBlockTextureWidth = 1 / blocksMixedTextureW;
    }
    void getBlockFaceUVsByTextureIndex(float uvs[8], int index)
    {
        uvs[0] = index % blocksMixedTextureW; //        uo
        uvs[1] = index / blocksMixedTextureW; //        vo

        uvs[2] = uvs[0] + perBlockTextureWidth; //      uo+1
        uvs[3] = uvs[1];                        //      vo

        uvs[4] = uvs[2];                        //      uo+1
        uvs[5] = uvs[1] + perBlockTextureWidth; //      vo+1

        uvs[6] = uvs[0]; //                             uo
        uvs[7] = uvs[5]; //                             vo+1
    }
};
