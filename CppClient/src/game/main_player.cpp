#include "main_player.h"
#include "App.h"

#include "ecs/CapsuleCollider.h"
// #include "ecs/ChunkRelated.h"
#include "ecs/VectorAbout.h"
// #include "ecs/sys/SyncPlayer.h"
#include "ecs/Tags.h"
// #include "io.h"
namespace VoxelFrame {
	namespace _Game {
		MainPlayer::MainPlayer() {
			cameraPtr = App::getInstance().getInstance().graphPtr->cameraPtr;
			IRegister_regist();
			this->getRigid().setType((rp3d::BodyType::DYNAMIC));
			this->getRigid().addCollider(Capsule_normal(), physic_engine::Transform_normal());
			this->getRigid().getCollider(0)->getMaterial().setBounciness(0);
			// this->getRigid().setType(rp3d::BodyType:)
			App::getInstance().getInstance().gamePtr->iUpdaterAfterPhysics.emplace_back(this);
			App::getInstance().getInstance().gamePtr->iUpdaterBeforePhysics.emplace_back(this);

			auto& ecs = *App::getInstance().ecsPtr;
			this->entityId =
				ecs.createEntity()
				.addComponent(_EcsComp::CapsuleCollider(&(this->getRigid())))
				.addEmptyComponent<_EcsComp::ChunkRelatedTag>()
				// .addEmptyComponent<_EcsComp::Position3D>()
				// .addEmptyComponent<_EcsComp::PlayerTag>()
				.entityId;
			App::getInstance().inputPtr->mouseMovePublisher.addListener(this);

			mainPlayerWorldOperator.init(this);

		}

		void MainPlayer::syncPositionAfterPhysic() {
			auto& pos = this->getRigid().getWorldPoint(rp3d::Vector3(0, 0, 0));

			{ //1. recalc chunk pos
				if (pos.x >= 0) {
					chunkX = (int)pos.x / VF_ChunkWidth;
				}
				else {
					chunkX = ((int)pos.x / VF_ChunkWidth) - 1;
				}
				if (pos.y >= 0) {
					chunkY = (int)pos.y / VF_ChunkWidth;
				}
				else {
					chunkY = ((int)pos.y / VF_ChunkWidth) - 1;
				}
				if (pos.z >= 0) {
					chunkZ = (int)pos.z / VF_ChunkWidth;
				}
				else {
					chunkZ = ((int)pos.z / VF_ChunkWidth) - 1;
				}
			}
			//2. sync camera
			cameraPtr->setPosition(pos.x, pos.y + 0.8, pos.z);
			// cameraPtr->Position;
		}

		void MainPlayer::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
			{
				auto bakYaw = cameraPtr->getYaw();
				auto bakPitch = cameraPtr->getPitch();
				xoffset *= MouseSensitivity;
				yoffset *= MouseSensitivity;

				//cameraPtr->Yaw += xoffset;/*
				//cameraPtr->Pitch += yoffset;*/
				bakYaw += xoffset;
				bakPitch += yoffset;

				// make sure that when pitch is out of bounds, screen doesn't get flipped
				if (constrainPitch) {
					if (bakPitch > 89.0f)
						bakPitch = 89.0f;
					if (bakPitch < -89.0f)
						bakPitch = -89.0f;
				}

				// update Front, Right and Up Vectors using the updated Euler angles
				cameraPtr->setEularAndUpdate(bakYaw, bakPitch);
			}
		}

		void MainPlayer::IRegister_regist() {
		}

		void MainPlayer::updateAfterPhysic() {
			this->syncPositionAfterPhysic();
		}

		void MainPlayer::updateBeforePhysic() {
			this->checkControl();
		}

		void MainPlayer::checkControl() {
			auto& app = App::getInstance();
			auto& input = *App::getInstance().inputPtr;

			rp3d::Vector3 velocity(0, 0, 0);

			if (input.getKey(Input_Key(W)) == Input_KeyState::KeyDown) {
				velocity += rp3d::Vector3(cameraPtr->getFront().x, 0, cameraPtr->getFront().z);
			}
			if (input.getKey(Input_Key(S)) == Input_KeyState::KeyDown) {
				velocity -= rp3d::Vector3(cameraPtr->getFront().x, 0, cameraPtr->getFront().z);
				// this->Key_Move(N_MainPlayer::BACKWARD, app.deltaTime);
			}
			if (input.getKey(Input_Key(A)) == Input_KeyState::KeyDown) {
				// this->Key_Move(N_MainPlayer::LEFT, app.deltaTime);
				velocity -= rp3d::Vector3(cameraPtr->getRight().x, 0, cameraPtr->getRight().z);
			}
			if (input.getKey(Input_Key(D)) == Input_KeyState::KeyDown) {
				// this->Key_Move(N_MainPlayer::RIGHT, app.deltaTime);
				velocity += rp3d::Vector3(cameraPtr->getRight().x, 0, cameraPtr->getRight().z);
			}
			velocity = velocity.getUnit() * app.deltaTime * 120;
			velocity.y = this->getRigid().getLinearVelocity().y;
			// }
			this->getRigid().setLinearVelocity(velocity);
		}

		void MainPlayer::MouseMove_ListenerCallback(int x, int y, int dx, int dy) {
			//如果当前视角锁定
			if (App::getInstance().graphPtr->gameWindow.cursor.getLocked()) {
				ProcessMouseMovement((float)dx, (float)-dy);
			}
		}
	}
}