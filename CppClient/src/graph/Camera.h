#ifndef __CAMER_H__
#define __CAMER_H__
#include "glad/glad.h"
#include <glm/glm.hpp>
namespace DrawSys
{
    class Camera
    {
    private:
        glm::vec3 camerPos;
        glm::vec3 cameraTarget;
        glm::vec3 cameraUp;
        glm::vec3 cameraFront;

    public:
        float pitch;
        float yaw;
        Camera();
        static Camera &GetInstance();
        glm::vec3 GetCameraPos();
        glm::vec3 GetCameraTarget();
        void SetCameraPos(glm::vec3 pos);
        void LookAt(int shaderprogram, glm::vec3 target);
        void SetViewRange(int shaderprogram, float angle, float height, float width);
        void ChangeView(int shaderprogram, float xoffset, float yoffset);
    };
}
#endif // __CAMER_H__