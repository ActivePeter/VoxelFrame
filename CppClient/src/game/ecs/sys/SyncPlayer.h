#pragma once
#include "../VectorAbout.h"
#include "../Tags.h"
#include "app.h"
namespace EcsSys
{
    void SyncPlayer(
        EcsComp::PlayerTag &tag,
        EcsComp::Position3D &pos)
    // EcsComp::PlayerTag *tag,
    // EcsComp::Position3D *pos)
    {
        // App::getInstance().gamePtr->mainPlayer->setPositionNoEcs(pos.x, pos.y, pos.z);

        auto &app = App::getInstance();
        auto &input = *app.inputPtr;
        auto window = App::getInstance().graphPtr->gameWindow.window;
        if (app.gamePtr)
        {
            auto &player = *app.gamePtr->mainPlayer;
            glm::vec3 *pos1 = (glm::vec3 *)&pos; //(pos.x, pos.y, pos.z);
            if (input.getKey(M_Input_KEY_W) == GLFW_PRESS)
            {
                player.Key_Move(N_MainPlayer::FORWARD, app.deltaTime, *pos1);
            }
            if (input.getKey(M_Input_KEY_S) == GLFW_PRESS)
            {
                player.Key_Move(N_MainPlayer::BACKWARD, app.deltaTime, *pos1);
            }
            if (input.getKey(M_Input_KEY_A) == GLFW_PRESS)
            {
                player.Key_Move(N_MainPlayer::LEFT, app.deltaTime, *pos1);
            }
            if (input.getKey(M_Input_KEY_D) == GLFW_PRESS)
            {
                player.Key_Move(N_MainPlayer::RIGHT, app.deltaTime, *pos1);
            }
            player.syncPositionFromEcs(*pos1);
        }
        // App::getInstance().gamePtr->mainPlayer->cameraPtr->Position.x = pos.x;
        // App::getInstance().gamePtr->mainPlayer->cameraPtr->Position.y = pos.y;
        // App::getInstance().gamePtr->mainPlayer->cameraPtr->Position.z = pos.z;

        // printf_s("SyncCamFromPlayer\r\n");
        // printf_s("%f %f %f\r\n", pos.x, pos.y, pos.z);
    }
}