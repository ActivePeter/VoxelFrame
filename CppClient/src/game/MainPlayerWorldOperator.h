
#pragma once
#include "base/vf_base.h"
#include "graph/Camera.h"
// #include "graph/CameraStateChangeEvent.h"
class MainPlayer;
//#include "graph/"
#include <iomanip>
namespace VoxelFrame
{
	namespace _Game
	{
		/**
		 * 用来完成玩家和世界的交互（放方块，拆方块，打动物，操作工具
		 */
		class MainPlayerWorldOperator : public VF::_Event::CameraStateChange_EventListener
		{

		public:
			MainPlayer *mainPlayer;
			//////////////////////////////////////////
			/**
			 * CameraStateChange_EventListener
			*/
			void CameraStateChange_EventListener::CameraStateChange_ListenerCallback(Camera &cam, const VF::_Event::CameraStateChangeType &stateChangeType) override
			{
				std::cout << "MainPlayerWorldOperator CameraStateChange_EventListener " << std::setprecision(5)
						  << cam.getFront().x << " "
						  << cam.getFront().y << " "
						  << cam.getFront().z << "\r\n";
			}
			//////////////////////////////////////////
			void init(MainPlayer *mainPlayer1);

			/*MainPlayerWorldOperator(MainPlayer *mainPlayer):mainPlayer(mainPlayer)
			{
				
			}*/
		};
	}
}
#include "main_player.h"