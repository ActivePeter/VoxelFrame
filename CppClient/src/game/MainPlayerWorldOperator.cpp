#include "MainPlayerWorldOperator.h"
#include <iomanip>
#include "physics/raycast.h"

namespace VoxelFrame
{
	namespace _Game
	{
		void MainPlayerWorldOperator::CameraStateChange_ListenerCallback(Camera& cam,
			const VF::_Event::CameraStateChangeType& stateChangeType)
		{
			if (stateChangeType == VF::_Event::CameraStateChangeType::Rotate) {
				//std::cout << "cam rotated" << std::endl;

				std::shared_ptr<_Chunk::Chunk> return_chunkPtr;
				int return_blockIndexInChunk;
				Type::Vec3I return_blockPosition;
				bool succ = _Physics::raycast2ChunkAndReturnBlock(cam.getPosition(), cam.getFront(), 10, return_chunkPtr, return_blockIndexInChunk, return_blockPosition);
				this->blockSelector.active = succ;
				this->blockSelector.position = return_blockPosition;
			}
		}

		void MainPlayerWorldOperator::init(MainPlayer* mainPlayer1)
		{
			mainPlayer = mainPlayer1;
			mainPlayer->cameraPtr->cameraStateChange_EventPublisher.addListener(this);
		}
	}
}