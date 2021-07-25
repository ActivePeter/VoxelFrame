#include "MainPlayerWorldOperator.h"
#include <iomanip>

namespace VoxelFrame
{
	namespace _Game
	{
		void MainPlayerWorldOperator::CameraStateChange_ListenerCallback(Camera& cam,
			const VF::_Event::CameraStateChangeType& stateChangeType)
		{

		}

		void MainPlayerWorldOperator::init(MainPlayer* mainPlayer1)
		{
			mainPlayer = mainPlayer1;
			mainPlayer->cameraPtr->cameraStateChange_EventPublisher.addListener(this);
		}
	}
}