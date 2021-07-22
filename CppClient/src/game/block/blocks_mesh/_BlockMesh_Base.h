class BlockMesh_Base;
#ifndef ___BLOCKMESH_BASE_H__
#define ___BLOCKMESH_BASE_H__

// #pragma once
#include "physic_engine/physic_engine.h"
#include "../block.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Block
        {
            class BlockMesh_Base
            {
            public:
                /**
                 * 获取r3d collider shape
                */
                virtual rp3d::BoxShape *getBlockColliderShape() = 0;

                /**
                 * 获取方块所有的网格三角形(以vertex序列和index序列表示)
                */
                virtual void getBlockValidTriangles(std::vector<Type::Vec3F> &vertexPoses, _Graph::Indices &indices) = 0;

                /**
                 * 获取某一面的顶点信息到序列里
                 *  （相对方块自身的坐标
                */
                virtual void pushOneFaceVerticesAndIndices_selfPos(
                    _Block::FaceDirection dir,
                    std::vector<Type::Vec3F> &vertexPoses,
                    std::vector<unsigned int> &indices, unsigned int vertexIndexOffset) = 0;

                /**************************************
                 * 方块基础信息1,判断某个方向是否有标准类型面
                 * 以便后续有特殊类型方块可以继承和覆盖
                 * ***************************************/
                virtual bool hasStandardFace(_Block::FaceDirection dir) = 0;
            };
        }
    }
}
#endif // ___BLOCKMESH_BASE_H__