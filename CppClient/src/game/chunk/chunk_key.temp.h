#include "chunk_key.h"

/**
 * 获取某一点对应的chunk的key
*/
template <typename PosVType>
void Key::getKeyOfPoint(Key &_return, PosVType px, PosVType py, PosVType pz)
{
    if (px >= 0)
    {
        _return.x = (int)px / VF_ChunkWidth;
    }
    else
    {
        _return.x = ((int)px / VF_ChunkWidth) - 1;
    }
    if (py >= 0)
    {
        _return.y = (int)py / VF_ChunkWidth;
    }
    else
    {
        _return.y = ((int)py / VF_ChunkWidth) - 1;
    }
    if (pz >= 0)
    {
        _return.z = (int)pz / VF_ChunkWidth;
    }
    else
    {
        _return.z = ((int)pz / VF_ChunkWidth) - 1;
    }
}

template <typename PosVType>
// std::tuple<PosVType, PosVType, PosVType>
Type::Vec3<PosVType>
Key::getChunkPosFromWorldPos(PosVType x, PosVType y, PosVType z)
{
    x -= VF_ChunkWidth * this->x;
    y -= VF_ChunkWidth * this->y;
    z -= VF_ChunkWidth * this->z;

    return Type::Vec3<PosVType>(x, y, z); // std::tuple<PosVType, PosVType, PosVType>(x, y, z);
}
