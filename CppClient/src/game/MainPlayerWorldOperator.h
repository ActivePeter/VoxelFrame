
#pragma once

#include "base/vf_base.h"
#include "graph/Camera.h"
// #include "graph/CameraStateChangeEvent.h"

//#include "graph/"

#include "block/BlockSelector.h"

namespace VoxelFrame
{
	namespace _Game
	{
		class MainPlayer;

		/**
		 * 用来完成玩家和世界的交互（放方块，拆方块，打动物，操作工具
		 */
		class MainPlayerWorldOperator : public VF::_Event::CameraStateChange_EventListener
		{

			//;

			MainPlayer* mainPlayer{};

		public:
			_Block::Selector blockSelector;
			//////////////////////////////////////////
			/**
			 * CameraStateChange_EventListener
			*/
			void CameraStateChange_ListenerCallback(Camera& cam,
				const VF::_Event::CameraStateChangeType& stateChangeType) override;

			//////////////////////////////////////////
			void init(MainPlayer* mainPlayer1);

			/*MainPlayerWorldOperator(MainPlayer *mainPlayer):mainPlayer(mainPlayer)
			{

			}*/
		};
	}
}

#include "main_player.h"