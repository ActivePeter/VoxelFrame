
//向前声明
class MainPlayer;
// enum MainPlayer::Movement;
// namespace _MainPlayer
// {
//     enum Movement;
// }

#ifndef __MAIN_PLAYER_H__
#define __MAIN_PLAYER_H__
#include "graph/Camera.h"
#include "chunk.h"
#include "interface/IRegister.h"
// #include "ecs/VectorAbout.h"

namespace N_MainPlayer
{
    enum Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
}
//当前玩家，并非指任意玩家
class MainPlayer : IRegister
{
private:
    void IRegister_regist() override;

public:
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    // enum Movement
    // {
    //     FORWARD,
    //     BACKWARD,
    //     LEFT,
    //     RIGHT
    // };
    float MovementSpeed = 2.5f;
    float MouseSensitivity = 0.1f;

    int chunkX = 0;
    int chunkY = 0;
    int chunkZ = 0;
    //将camera移到player下
    std::shared_ptr<Camera> cameraPtr;
    paecs::EntityID entityId;

    MainPlayer();
    glm::vec3 getPosition()
    {
        return cameraPtr->Position;
    }
    void syncPositionFromEcs(glm::vec3 pos);

    /**
     * Player Control
    */
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Key_Move(N_MainPlayer::Movement direction, float deltaTime,
                  glm::vec3 &pos)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == N_MainPlayer::FORWARD)
            // cameraPtr->Position += cameraPtr->Front * velocity;
            pos = (pos + cameraPtr->Front * velocity);
        if (direction == N_MainPlayer::BACKWARD)
            // cameraPtr->Position -= cameraPtr->Front * velocity;
            pos = (pos - cameraPtr->Front * velocity);
        if (direction == N_MainPlayer::LEFT)
            // cameraPtr->Position -= cameraPtr->Right * velocity;
            pos = (pos - cameraPtr->Right * velocity);
        if (direction == N_MainPlayer::RIGHT)
            // cameraPtr->Position += cameraPtr->Right * velocity;
            pos = (pos + cameraPtr->Right * velocity);
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        cameraPtr->Yaw += xoffset;
        cameraPtr->Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (cameraPtr->Pitch > 89.0f)
                cameraPtr->Pitch = 89.0f;
            if (cameraPtr->Pitch < -89.0f)
                cameraPtr->Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        cameraPtr->updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        auto &Zoom = cameraPtr->Zoom;
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }
};
#endif // __MAIN_PLAYER_H__