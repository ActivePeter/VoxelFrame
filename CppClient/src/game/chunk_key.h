#pragma once
#include "base.h"
#include "parallel_hashmap/phmap.h"

struct ChunkKey
{
    int32_t x;
    int32_t y;
    int32_t z;

    bool operator==(const ChunkKey &o) const
    {
        return x == o.x && y == o.y && z == o.z;
    }
    friend size_t hash_value(const ChunkKey &p)
    {
        return phmap::HashState().combine(0, p.x, p.y, p.z);
    }

    ChunkKey(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z)
    {
    }
    /**
     * 获取一个整数点对应的chunk坐标
    */
    template <typename PosVType>
    static void getChunkKeyOfPoint(ChunkKey &_return, PosVType x, PosVType y, PosVType z);
    /**
     * 获取一个点对应的chunk坐标
    */
    // static void getChunkKeyOfPoint(ChunkKey &_return, float x, float y, float z);
    // ChunkKey(float px, float py, float pz);
    ChunkKey() {}
};
#include "chunk_key.temp.h"