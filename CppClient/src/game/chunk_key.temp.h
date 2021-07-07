#include "chunk_key.h"
template <typename PosVType>
void ChunkKey::getChunkKeyOfPoint(ChunkKey &_return, PosVType px, PosVType py, PosVType pz)
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