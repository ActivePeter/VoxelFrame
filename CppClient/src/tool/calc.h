#pragma once
#include "math.h"
#include "glm/glm.hpp"
namespace VoxelFrame
{
    inline float vec3Len(float x, float y, float z)
    {
        return sqrtf(x * x + y * y + z * z);
    }
    inline float vec3Len(glm::vec3 &vec)
    {
        return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    }
    // inline
}