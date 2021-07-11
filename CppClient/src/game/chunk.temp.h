#pragma once

template <typename PosType>
void Chunk::turnInWorldPos2InChunkPos(PosType &x, PosType &y, PosType &z)
{
    x = x - ((int)x) / VF_ChunkWidth * VF_ChunkWidth;
    y = y - ((int)y) / VF_ChunkWidth * VF_ChunkWidth;
    z = z - ((int)z) / VF_ChunkWidth * VF_ChunkWidth;

    if (x < 0)
    {
        x += VF_ChunkWidth;
    }
    if (y < 0)
    {
        y += VF_ChunkWidth;
    }
    if (z < 0)
    {
        z += VF_ChunkWidth;
    }
}

// void ChunkKey::getChunkKeyOfPoint(ChunkKey &_return, int32_t px, int32_t py, int32_t pz)

// void ChunkKey::getChunkKeyOfPoint(ChunkKey &_return, float px, float py, float pz)
// {
//     if (px >= 0)
//     {
//         _return.x = (int)px / VF_ChunkWidth;
//     }
//     else
//     {
//         _return.x = ((int)px / VF_ChunkWidth) - 1;
//     }
//     if (py >= 0)
//     {
//         _return.y = (int)py / VF_ChunkWidth;
//     }
//     else
//     {
//         _return.y = ((int)py / VF_ChunkWidth) - 1;
//     }
//     if (pz >= 0)
//     {
//         _return.z = (int)pz / VF_ChunkWidth;
//     }
//     else
//     {
//         _return.z = ((int)pz / VF_ChunkWidth) - 1;
//     }
// }
