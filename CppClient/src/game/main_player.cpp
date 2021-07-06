#include "main_player.h"
#include "App.h"

#include "ecs/CapsuleCollider.h"
// #include "ecs/ChunkRelated.h"
#include "ecs/VectorAbout.h"
// #include "ecs/sys/SyncPlayer.h"
#include "ecs/Tags.h"
// #include "io.h"

MainPlayer::MainPlayer()
{
    cameraPtr = App::getInstance().getInstance().graphPtr->cameraPtr;
    IRegister_regist();
    this->getRigid().setType((rp3d::BodyType::DYNAMIC));
    this->getRigid().addCollider(Capsule_normal(), physic_engine::Transform_normal());
    this->getRigid().getCollider(0)->getMaterial().setBounciness(0);
    // this->getRigid().setType(rp3d::BodyType:)
    App::getInstance().getInstance().gamePtr->iUpdaterAfterPhysics.emplace_back(this);
    App::getInstance().getInstance().gamePtr->iUpdaterBeforePhysics.emplace_back(this);

    auto &ecs = *App::getInstance().ecsPtr;
    this->entityId =
        ecs.createEntity()
            .addComponent(EcsComp::CapsuleCollider(&(this->getRigid())))
            .addEmptyComponent<EcsComp::ChunkRelatedTag>()
            // .addEmptyComponent<EcsComp::Position3D>()
            // .addEmptyComponent<EcsComp::PlayerTag>()
            .entityId;

    // App::getInstance()
    //     .ecsPtr->addSysByFunc(EcsSys::SyncPlayer);
}

void MainPlayer::syncPositionAfterPhysic()
{
    auto &pos = this->getRigid().getWorldPoint(rp3d::Vector3(0, 0, 0));
    { //1. recalc chunk pos
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
    //2. sync camera
    cameraPtr->setPosition(pos.x, pos.y + 0.8, pos.z);
    // cameraPtr->Position;
}
/**
 * physic about
*/
// void MainPlayer::syncPhysic()
// {
// }

// void MainPlayer::syncPositionFromEcs(glm::vec3 pos)
// {
//     // setPositionNoEcs(pos.x, pos.y, pos.z);
//     { //recalc chunk pos
//         if (pos.x >= 0)
//         {
//             chunkX = (int)pos.x / VF_ChunkWidth;
//         }
//         else
//         {
//             chunkX = ((int)pos.x / VF_ChunkWidth) - 1;
//         }
//         if (pos.y >= 0)
//         {
//             chunkY = (int)pos.y / VF_ChunkWidth;
//         }
//         else
//         {
//             chunkY = ((int)pos.y / VF_ChunkWidth) - 1;
//         }
//         if (pos.z >= 0)
//         {
//             chunkZ = (int)pos.z / VF_ChunkWidth;
//         }
//         else
//         {
//             chunkZ = ((int)pos.z / VF_ChunkWidth) - 1;
//         }
//     }
//     cameraPtr->Position = pos;
//     // cameraPtr->Position = pos;
//     // App::getInstance().ecsPtr->
// }

// void MainPlayer::Key_Move(N_MainPlayer::Movement direction, float deltaTime,
//                           glm::vec3 &pos)
// {
//     {
//         float velocity = MovementSpeed * deltaTime;
//         if (direction == N_MainPlayer::FORWARD)
//             // cameraPtr->Position += cameraPtr->Front * velocity;
//             pos = (pos + cameraPtr->Front * velocity);
//         if (direction == N_MainPlayer::BACKWARD)
//             // cameraPtr->Position -= cameraPtr->Front * velocity;
//             pos = (pos - cameraPtr->Front * velocity);
//         if (direction == N_MainPlayer::LEFT)
//             // cameraPtr->Position -= cameraPtr->Right * velocity;
//             pos = (pos - cameraPtr->Right * velocity);
//         if (direction == N_MainPlayer::RIGHT)
//             // cameraPtr->Position += cameraPtr->Right * velocity;
//             pos = (pos + cameraPtr->Right * velocity);
//     }
// }

void MainPlayer::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
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
}

void MainPlayer::ProcessMouseScroll(float yoffset)
{
    {
        auto &Zoom = cameraPtr->Zoom;
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }
}

void MainPlayer::IRegister_regist()
{
    auto &input = *App::getInstance().inputPtr;
    input.registerMouseMove(
        [](double xpos, double ypos, double dx, double dy)
        {
            // // camera 操作
            // static bool firstMouse = true;
            // static double lastX, lastY;
            // if (firstMouse)
            // {
            //     lastX = xpos;
            //     lastY = ypos;
            //     firstMouse = false;
            // }

            // float xoffset = xpos - lastX;
            // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

            // lastX = xpos;
            // lastY = ypos;

            auto gamePtr = App::getInstance().gamePtr;
            auto &cursor = App::getInstance().graphPtr->gameWindow.cursor;
            if (gamePtr && cursor.getLocked())
            {
                gamePtr->mainPlayer->ProcessMouseMovement((float)dx, (float)-dy);
            }
            // if (App::getInstance().graphPtr && App::getInstance().graphPtr->cameraPtr)
            // {
            //     App::getInstance().graphPtr->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
            // }
        });
}

void MainPlayer::updateAfterPhysic()
{
    this->syncPositionAfterPhysic();
}

void MainPlayer::updateBeforePhysic()
{
    this->checkControl();
}
void MainPlayer::checkControl()
{
    auto &app = App::getInstance();
    auto &input = *App::getInstance().inputPtr;

    rp3d::Vector3 velocity(0, 0, 0);

    if (input.getKey(M_Input_KEY_W) == Input_KeyState::E_KeyDown)
    {
        velocity += rp3d::Vector3(cameraPtr->Front.x, 0, cameraPtr->Front.z);
    }
    if (input.getKey(M_Input_KEY_S) == Input_KeyState::E_KeyDown)
    {
        velocity -= rp3d::Vector3(cameraPtr->Front.x, 0, cameraPtr->Front.z);
        // this->Key_Move(N_MainPlayer::BACKWARD, app.deltaTime);
    }
    if (input.getKey(M_Input_KEY_A) == Input_KeyState::E_KeyDown)
    {
        // this->Key_Move(N_MainPlayer::LEFT, app.deltaTime);
        velocity -= rp3d::Vector3(cameraPtr->Right.x, 0, cameraPtr->Right.z);
    }
    if (input.getKey(M_Input_KEY_D) == Input_KeyState::E_KeyDown)
    {
        // this->Key_Move(N_MainPlayer::RIGHT, app.deltaTime);
        velocity += rp3d::Vector3(cameraPtr->Right.x, 0, cameraPtr->Right.z);
    }
    velocity = velocity.getUnit() * app.deltaTime * 120;
    velocity.y = this->getRigid().getLinearVelocity().y;
    // }
    this->getRigid().setLinearVelocity(velocity);
}