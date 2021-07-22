
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
#include "chunk/chunk.h"
#include "interface/IRegister.h"
#include "physics/rigid.h"
#include "physics/collision_shape.h"
#include "game/interfaces/IUpdaterAfterPhysic.h"
#include "game/interfaces/IUpdaterBeforePhysic.h"
#include "system_related/MouseMoveEvent.h"
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
class MainPlayer
    : public IRegister,
      public Rigid,
      public Capsule,
      public IUpdaterAfterPhysic,
      public IUpdaterBeforePhysic,
      public VF::MouseMoveEventListener
//   public VF::ListenerClass(MouseMove)
{
    ///////////////////////
    //      MouseMove
public:
    void ListenerCallback(MouseMove)(int x, int y, int dx, int dy) override;
    ///////////////////////
    //
    //      IUpdaterAfterPhysic
public:
    /**
     * 在物理更新前
    */
    void updateAfterPhysic() override;

    ///////////////////////
    //
    //      IUpdaterBeforePhysic
public:
    /**
     * 在物理更新后
    */
    void updateBeforePhysic() override;

    ///////////////////////
    //
    //      Capsule
private: //func
    rp3d::CapsuleShape *Capsule_normal() override
    {
        float r = 0.4f;
        float h = 0.8f;
        static rp3d::CapsuleShape *normal = nullptr;
        if (!normal)
        {
            normal = physic_engine::physicCommon().createCapsuleShape(r, h);
        }

        return normal;
    }

    ///////////////////////
    //
    //      IRegister
    void IRegister_regist() override;

public: //var
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

public: //func
    MainPlayer();
    // void syncPhysic() override;
    // void beforePhysic() override;
    //将camera移到player下
    std::shared_ptr<Camera> cameraPtr;
    paecs::EntityID entityId;

    glm::vec3 getPosition()
    {
        return cameraPtr->Position;
    }

    void syncPositionAfterPhysic();

    /**
     * Player Control
    */
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    // void Key_Move(N_MainPlayer::Movement direction, float deltaTime,
    //               glm::vec3 &pos);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    /**
     * 检查控制操作
    */
    void checkControl();
};
#endif // __MAIN_PLAYER_H__