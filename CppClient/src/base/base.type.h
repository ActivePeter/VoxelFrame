#pragma once
#include "glm/glm.hpp"
namespace VoxelFrame
{
    namespace Type
    {
        using Vec3F = glm::vec3;
        using Vec3I = glm::ivec3;

        template <typename T>
        using Vec3 = glm::vec<3, T, glm::defaultp>;
    }
}