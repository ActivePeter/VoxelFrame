
//向前声明
class MainPlayer;
// enum MainPlayer::Movement;
// namespace _MainPlayer
// {
//     enum Movement;
// }
#include "graph/Camera.h"
#include "chunk.h"

#ifndef __MAIN_PLAYER_H__
#define __MAIN_PLAYER_H__

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
class MainPlayer
{
private:
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

    MainPlayer();
    glm::vec3 getPosition()
    {
        return cameraPtr->Position;
    }
    void setPosition(glm::vec3 pos)
    {
        { //recalc chunk pos
            if (pos.x >= 0)
            {
                chunkX = (int)pos.x / VF_ChunkWidth;
            }
            else
            {
                chunkX = ((int)pos.x / VF_ChunkWidth) - 1;
            }
            if (pos.y >= 0)
            {
                chunkY = (int)pos.y / VF_ChunkWidth;
            }
            else
            {
                chunkY = ((int)pos.y / VF_ChunkWidth) - 1;
            }
            if (pos.z >= 0)
            {
                chunkZ = (int)pos.z / VF_ChunkWidth;
            }
            else
            {
                chunkZ = ((int)pos.z / VF_ChunkWidth) - 1;
            }
        }

        // int intx=(int)pos.x;
        // int inty=(int)pos.y;
        // int intz=(int)pos.z;
        // if(intx)

        // chunkY = (int)pos.y / VF_ChunkWidth;
        // chunkZ = (int)pos.z / VF_ChunkWidth;

        // printf("player setPosition %f,%f,%f,\r\n%d,%d,%d\r\n",

        //        pos.x, pos.y, pos.z, chunkX,
        //        chunkY,
        //        chunkZ);
        cameraPtr->Position = pos;
    }

    /**
     * Player Control
    */
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(N_MainPlayer::Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == N_MainPlayer::FORWARD)
            // cameraPtr->Position += cameraPtr->Front * velocity;
            setPosition(getPosition() + cameraPtr->Front * velocity);
        if (direction == N_MainPlayer::BACKWARD)
            // cameraPtr->Position -= cameraPtr->Front * velocity;
            setPosition(getPosition() - cameraPtr->Front * velocity);
        if (direction == N_MainPlayer::LEFT)
            // cameraPtr->Position -= cameraPtr->Right * velocity;
            setPosition(getPosition() - cameraPtr->Right * velocity);
        if (direction == N_MainPlayer::RIGHT)
            // cameraPtr->Position += cameraPtr->Right * velocity;
            setPosition(getPosition() + cameraPtr->Right * velocity);
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