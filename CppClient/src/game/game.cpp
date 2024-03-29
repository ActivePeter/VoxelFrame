#include "game.h"
#include "system_related/_sys_api.h"
#include "ecs/sys/Physic.h"
#include "physic_engine/physic_engine.h"
#include "imgui.h"

namespace VoxelFrame {
	namespace _Game {
		/**
 *
 *game start 之前应当加载完毕所有引擎层内容
 *
*/
		void Game::start() {
			//chunkMa
			//因为game是父元素，所以传给子元素引用就行，game管理子元素的生命周期
			chunkManager = std::make_shared<_Chunk::Manager>();
			blockManager = std::make_shared<_Block::Manager>();
			mainPlayer = std::make_shared<MainPlayer>();
			// Manager->addNewChunk(0, 0, 0);

			//注册锁住摄像头的触发事件
			// registry::game_ControllingSwitch();
			IRegister_regist();
			playing = true;
			App::getInstance().ecsPtr->addSys2Group(
				this->beforePhysicSysGroup,
				_Game::_EcsSys::updateChunkColliderForChunkRelated);

			App::getInstance().graphPtr->_guiPtr->guiNothingClick_EventPublisher.addListener(this);
		}

		/**
		 * 游戏内容循环刷新函数
		 *   1.判断并调用周期性回调函数
		*/
		void Game::loop() {
			for (int i = 0; i < TCallers.size(); i++) {
				if (gameTick % TCallers[i].T == 0) {
					TCallers[i].callAll(*this);
				}
			}

			// int t1 = (int)(1000 * glfwGetTime());
			auto t1 = _sys_api_getTick();
			chunkManager->resetAllChunkInactived();
			// int t2 = (int)(1000 * glfwGetTime());
			auto t2 = _sys_api_getTick();
			this->beforePhysicSysGroup.runAll();
			// int t3 = (int)(1000 * glfwGetTime());
			auto t3 = _sys_api_getTick();
			chunkManager->updateAllChunkPhysic();
			auto t4 = _sys_api_getTick();
			// int t4 = (int)(1000 * glfwGetTime());
			// printf_s("time spent %d %d %d\r\n", t2 - t1, t3 - t2, t4 - t3);
			// this->Manager->
			for (auto& i : iUpdaterBeforePhysics) {
				i->updateBeforePhysic();
			}
			physic_engine::physicWorld().update(1.0f / 60);
			this->afterPhysicSysGroup.runAll();
			for (auto& i : iUpdaterAfterPhysics) {
				i->updateAfterPhysic();
			}
			// App::getInstance().ecsPtr->loop();

			gameTick++;
		}

		/**注册周期性回调函数
 * 没有重复性检测
 * **/
		void Game::registTCallback(int T, TCallbackFunc f) {
			int foundIndex = -1;
			for (int i = 0; i < TCallers.size(); i++) {
				if (TCallers[i].T == T) {
					foundIndex = i;
					//找到了
					break;
				}
			}
			if (foundIndex == -1) {
				TCallers.push_back(TCaller(T));
				foundIndex = (int)TCallers.size() - 1;
			}

			TCallers[foundIndex].callbacks.push_back(f);
		}

		void Game::IRegister_regist() {
			//set focus when playing
			// auto &game = *this;
			auto& input = *App::getInstance().inputPtr;
			input.registerMouseClick(
				[](int btn, int action) {
					auto& game = *App::getInstance().gamePtr;
					// if (btn == M_Input_MOUSE_BUTTON_LEFT && action == Input_KeyState::E_KeyDown)
					// {
					//     if (game.playing)
					//     {
					//         App::getInstance().graphPtr->gameWindow.cursor.setLocked(true);
					//     }
					// }
				});
			input.registerProcessInput(
				[](Input& input) {
					if (input.getKey(Input_Key(ESCAPE)) == Input_KeyState::KeyDown) {
						App::getInstance().graphPtr->gameWindow.cursor.setLocked(false);
					}
					// auto &app = App::getInstance();
					// auto window = App::getInstance().graphPtr->gameWindow.window;
					// if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					// {
					// }
				});
		}

		void Game::GuiNothingClick_ListenerCallback() {
			printf("gui nothing clicked");
			// Imgui
			// ImGui::GetIO().MouseDrawCursor = false;
			App::getInstance().graphPtr->gameWindow.cursor.setLocked(true);
		}
	}
}