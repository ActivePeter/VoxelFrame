#pragma once
#include "graph/Mesh.h"
namespace VoxelFrame
{
	namespace _Game
	{
		// class Manager;
		/////////////////////
		namespace _Block
		{
			class Selector :public _Graph::Mesh
			{
			public:
				Type::Vec3I position;
				bool active = false;
			private:
				void bindTexture() override {};
			};
		}
	}
}
