#include "MainPlayerWorldOperator.h"
namespace VoxelFrame
{
	namespace _Game
	{
		void MainPlayerWorldOperator::init(MainPlayer *mainPlayer1)
		{
			mainPlayer = mainPlayer1;
			mainPlayer->cameraPtr->cameraStateChange_EventPublisher.addListener(this);
		}
	}
}