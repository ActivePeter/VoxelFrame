class Camera;

#ifndef CAMERA_H
#define CAMERA_H

#include "base/vf_base.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "CameraStateChangeEvent.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
// const float SPEED = 2.5f;
// const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{

    // camera Attributes
    VF::Type::Vec3F Position;
    VF::Type::Vec3F Front;
    VF::Type::Vec3F Up;
    VF::Type::Vec3F Right;
    VF::Type::Vec3F WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options

    float Zoom;
    /**
	 * 更新camera的状态，同时，应该发布一个camera方向改变的publisher
	 * 这样便能实现摄像头方向改变时的一些操作，
	 * （重新计算方块选中位置
	*/
    void updateCameraVectors()
    {
        // calculate the new Front vector
        VF::Type::Vec3F front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front,
                                          WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

public:
    VF::_Event::CameraStateChange_EventPublisher cameraStateChange_EventPublisher;

    inline VF::Type::Vec3F getPosition()
    {
        return Position;
    }
    inline float getYaw()
    {
        return Yaw;
    }
    inline float getPitch()
    {
        return Pitch;
    }
    inline VF::Type::Vec3F getFront()
    {
        return Front;
    }
    inline VF::Type::Vec3F getRight()
    {
        return Right;
    }
    inline float getZoom()
    {
        return Zoom;
    }
    // constructor with vectors
    Camera(VF::Type::Vec3F position = VF::Type::Vec3F(-1.0f, 60.0f, -1.0f), VF::Type::Vec3F up = VF::Type::Vec3F(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) : Front(VF::Type::Vec3F(0.0f, 0.0f, -1.0f)), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
                                                                                                              VF::Type::Vec3F(0.0f, 0.0f, -1.0f)),
                                                                                                          Zoom(ZOOM)
    {
        Position = VF::Type::Vec3F(posX, posY, posZ);
        WorldUp = VF::Type::Vec3F(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        // updateCameraVectors();
        return glm::lookAt(Position, Position + Front, Up);
    }

    inline void setPosition(float x, float y, float z)
    {
        Position.x = x;
        Position.y = y;
        Position.z = z;
    }

    inline void setEularAndUpdate(float yaw, float pitch)
    {
        Yaw = yaw;
        Pitch = pitch;
        cameraStateChange_EventPublisher.pub2All(*this, VF::_Event::CameraStateChangeType::Rotate);
        updateCameraVectors();
    }

private:
};

#endif