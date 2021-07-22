#pragma once
#include "base/vf_base.h"
#include "parallel_hashmap/phmap.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Chunk
        {
            struct Key
            {
                int32_t x;
                int32_t y;
                int32_t z;

                bool operator==(const Key &o) const
                {
                    return x == o.x && y == o.y && z == o.z;
                }
                friend size_t hash_value(const Key &p)
                {
                    return phmap::HashState().combine(0, p.x, p.y, p.z);
                }

                Key(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z)
                {
                }
                /**
     * 获取一个整数点对应的chunk坐标
    */
                template <typename PosVType>
                static void getKeyOfPoint(Key &_return, PosVType x, PosVType y, PosVType z);
                /**
     * 将世界坐标转换为区块中坐标
    */
                template <typename PosVType>
                // std::tuple<PosVType, PosVType, PosVType>
                Type::Vec3<PosVType> getChunkPosFromWorldPos(PosVType x, PosVType y, PosVType z);
                /**
     * 获取一个点对应的chunk坐标
    */
                // static void getKeyOfPoint(Key &_return, float x, float y, float z);
                // Key(float px, float py, float pz);
                Key() {}
            };
#include "chunk_key.temp.h"
        }
    }
}
