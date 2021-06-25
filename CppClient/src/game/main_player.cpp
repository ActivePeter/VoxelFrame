#include "main_player.h"
#include "App.h"

#include "ecs/CapsuleCollider.h"
#include "ecs/ChunkRelated.h"
#include "ecs/VectorAbout.h"
#include "ecs/sys/SyncPlayer.h"
#include "ecs/Tags.h"
// #include "io.h"

MainPlayer::MainPlayer()
{
    cameraPtr = App::getInstance().getInstance().graphPtr->cameraPtr;
    IRegister_regist();
    auto &ecs = *App::getInstance().ecsPtr;
    this->entityId = ecs.createEntity()
                         .addEmptyComponent<EcsComp::CapsuleCollider>()
                         .addEmptyComponent<EcsComp::ChunkRelated>()
                         .addEmptyComponent<EcsComp::Position3D>()
                         .addEmptyComponent<EcsComp::PlayerTag>()
                         .entityId;

    App::getInstance()
        .ecsPtr->addSysByFunc(EcsSys::SyncPlayer);
}

void MainPlayer::syncPositionFromEcs(glm::vec3 pos)
{
    // setPositionNoEcs(pos.x, pos.y, pos.z);
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
    cameraPtr->Position = pos;
    // cameraPtr->Position = pos;
    // App::getInstance().ecsPtr->
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
    // input.registerProcessInput(
    //     [](Input &input)
    //     {
    //         auto &app = App::getInstance();
    //         auto window = App::getInstance().graphPtr->gameWindow.window;
    //         if (app.gamePtr)
    //         {
    //             auto &player = *app.gamePtr->mainPlayer;
    //             if (input.getKey(M_Input_KEY_W) == GLFW_PRESS)
    //             {
    //                 player.ProcessKeyboard(N_MainPlayer::FORWARD, app.deltaTime);
    //             }
    //             if (input.getKey(M_Input_KEY_S) == GLFW_PRESS)
    //             {
    //                 player.ProcessKeyboard(N_MainPlayer::BACKWARD, app.deltaTime);
    //             }
    //             if (input.getKey(M_Input_KEY_A) == GLFW_PRESS)
    //             {
    //                 player.ProcessKeyboard(N_MainPlayer::LEFT, app.deltaTime);
    //             }
    //             if (input.getKey(M_Input_KEY_D) == GLFW_PRESS)
    //             {
    //                 player.ProcessKeyboard(N_MainPlayer::RIGHT, app.deltaTime);
    //             }
    //         }
    //     });
}
