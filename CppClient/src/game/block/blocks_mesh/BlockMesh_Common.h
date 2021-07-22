#pragma once
#include "base/vf_base.h"
#include "_BlockMesh_Base.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Block
        {
            class BlockMesh_Common : public BlockMesh_Base
            {
                friend class Manager;

                /* BlockMesh_Base *******************************************************/
                void getBlockValidTriangles(std::vector<Type::Vec3F> &vertexPoses, _Graph::Indices &indices) override;

                rp3d::BoxShape *getBlockColliderShape() override
                {
                    static rp3d::BoxShape *boxShape;
                    if (!boxShape)
                    {
                        boxShape = physic_engine::physicCommon().createBoxShape(rp3d::Vector3(0.5, 0.5, 0.5));
                    }
                    return boxShape;
                }

                void pushOneFaceVerticesAndIndices_selfPos(
                    _Block::FaceDirection dir,
                    std::vector<Type::Vec3F> &vertexPoses,
                    _Graph::Indices &indices, unsigned int vertexIndexOffset) override;

                bool hasStandardFace(_Block::FaceDirection dir) override
                {
                    return true;
                }

                /**************************************************************************/
            protected:
                /**
     * 根据四个序号 初始化（获取到vertices里）一面的顶点坐标
    */
                inline void setFaceVertices(std::vector<Type::Vec3F> &vertexPoses, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3)
                {
                    Type::Vec3F model(0, 0, 0);
                    vertexPoses.push_back(model);
                    vertexPoses.push_back(model);
                    vertexPoses.push_back(model);
                    vertexPoses.push_back(model);
                    addUpStandardVertexOfIndex(vertexPoses[vertexPoses.size() - 4], _0);
                    addUpStandardVertexOfIndex(vertexPoses[vertexPoses.size() - 3], _1);
                    addUpStandardVertexOfIndex(vertexPoses[vertexPoses.size() - 2], _2);
                    addUpStandardVertexOfIndex(vertexPoses[vertexPoses.size() - 1], _3);
                }
                /* data */
                // void setFaceUVsByTextureIndex(
                //     Mesh &mesh, int textureIndex);

                /**************************************
     * 方块基础信息3
     * 这个函数包含方块 顶点相对坐标 和 对应的index
     * 参考markdown文件夹里的 方块顶点顺序.md
     * ***************************************/
                void addUpStandardVertexOfIndex(Type::Vec3F &vertexPos, uint8_t index);

            public:
                /**
     * 空的Info的构造函数
    */
                BlockMesh_Common() {}

                /**************************************
     * 方块基础信息2
     * 这个函数包含方块每个面的顶点坐标顺序
     * 以便后续有特殊类型方块可以继承和覆盖
     * ***************************************/
                void setFaceVertexPosOnDir(std::vector<Type::Vec3F> &vertexPoses, _Block::FaceDirection dir);
                // virtual void setVertexUVOnDir(_Block::FaceDirection dir, Mesh &mesh) {}

                // /**************************************
                //  * 往区块网格添加一个方块面的函数
                //  * 包含了三角形的顺序信息（indices
                //  * 顶点信息（vertices
                //  * 材质信息（uv
                //  *
                //  * 网格是区块网格，所以要加上方块的坐标作为顶点的偏移
                //  * ***************************************/
                // void pushOneFace2Mesh(int blockx, int blocky, int blockz, _Block::FaceDirection dir, Mesh &mesh);
            };
        }
    }
}