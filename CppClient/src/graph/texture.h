#pragma once
#include "base.h"
#include "opencv2/opencv.hpp"
#include "math.h"
//负责接收注册和构建贴图
class TextureManager
{
private:
    //合并后的材质宽度上方块数量
    int blocksMixedTextureW = 1;
    float perBlockTextureWidth2UV = 1; //需要在最后变为  1/ blocksMixedTextureW; //单个材质的uv宽度
    int faceCnt = 0;
    list<cv::Mat> blockFacesBuffer;
    const int blockFaceTextureWidth = 32;

    /* data */
public:
    unsigned int chunkTexture;
    TextureManager()
    {
        //set up chunk texture
        glGenTextures(1, &chunkTexture);
        bindChunkTexture();
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    inline void bindChunkTexture()
    {
        glBindTexture(GL_TEXTURE_2D, chunkTexture);
    }
    /**
     * 注册方块一面的贴图
     * **/
    int registBlockFaceTexture(std::string TextureFileName)
    {
        faceCnt++;
        //读取文件，加入总的材质面板里
        auto a = cv::imread("./resource/images/" + TextureFileName + ".png");
        cv::imshow("ss", a);
        blockFacesBuffer.push_back(a);
        return faceCnt - 1;
    }
    void registBlockFacesEnd()
    {
        int sqrCnt = (int)sqrt(faceCnt);
        if (sqrCnt * sqrCnt == faceCnt)
        {
            blocksMixedTextureW = sqrCnt;
        }
        else
        {
            blocksMixedTextureW = sqrCnt + 1;
        }
        perBlockTextureWidth2UV = 1.0f / blocksMixedTextureW;
        //这里开始拼接图片
        //创建目标拷贝
        cv::Mat dst(blockFaceTextureWidth * blocksMixedTextureW,
                    blockFaceTextureWidth * blocksMixedTextureW, blockFacesBuffer.back().type());
        //遍历图片并拼接到目标图片，同时在每次循环结尾清除节点（释放mat
        int index = 0;
        for (auto iter = blockFacesBuffer.begin(); iter != blockFacesBuffer.end();)
        {
            int offsetx = index % blocksMixedTextureW * blockFaceTextureWidth;
            int offsety = index / blocksMixedTextureW * blockFaceTextureWidth;
            //区域筛选器
            cv::Mat imageROI = dst(cv::Rect(offsetx, offsety, blockFaceTextureWidth, blockFaceTextureWidth));
            iter->copyTo(imageROI);
            // cv::imshow("combine" + index, (*iter));
            //节点++必须要在函数内自增。因为执行完节点就已经销毁了
            //清除节点的过程也是释放mat，因为mat是智能指针
            blockFacesBuffer.erase(iter++);
            index++;
        }
        // cv::imshow("combine", dst);
        //将图片注册为opengl的材质
        bindChunkTexture();
        cv::imshow("mixed", dst);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dst.cols, dst.rows, 0, GL_BGR, GL_UNSIGNED_BYTE,
                     dst.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    void getBlockFaceUVsByTextureIndex(float uvs[8], int index)
    {
        uvs[0] = float(index % blocksMixedTextureW); //        uo
        uvs[1] = float(index / blocksMixedTextureW); //        vo
        uvs[2] = uvs[0] + perBlockTextureWidth2UV;   //      uo+1
        uvs[3] = uvs[1];                             //      vo
        uvs[4] = uvs[2];                             //      uo+1
        uvs[5] = uvs[1] + perBlockTextureWidth2UV;   //      vo+1
        uvs[6] = uvs[0];                             //                             uo
        uvs[7] = uvs[5];                             //                             vo+1
    }
};
