#pragma once
#include <glm/glm.hpp>
#include "base/vf_base.h"
#include "game/chunk/chunk.h"
#include "app.h"
// #include "math.h"
// #include "tool/calc.h"
#include "numeric"
// #include "main_player.h"
namespace VoxelFrame
{
	namespace _Game
	{
		namespace _Physics
		{
			//推导过程 见 {$workspace}/markdown/record.md 7.14
			bool raycast2Triangle(
				const Type::Vec3F& startPoint,
				const Type::Vec3F& direction, const Type::Vec3F& triP1, const Type::Vec3F& triP2, const Type::Vec3F& triP3,
				Type::Vec3F& return_cross);

			/**
			 * 与三角形碰撞并返回离射线最近的碰撞点，若无碰撞返回false
			*/
			bool raycast2TrianglesNearest(
				const Type::Vec3F& startPoint, const Type::Vec3F& direction,
				std::vector<Type::Vec3F>& vertexPoses, _Graph::Indices& indices, Type::Vec3F& return_colidPoint);
			/**
			 * 射线检测是否碰到方块，
			 *      若碰到方块，返回方块所在区块的指针以及方块的序号，
			 *      若没碰到，指针为空
			*/
			bool raycast2ChunkAndReturnBlock(
				const Type::Vec3F& startPoint,
				const Type::Vec3F& direction,
				float maxRange,
				std::shared_ptr<_Chunk::Chunk>& return_chunkPtr,
				int& return_blockIndexInChunk, Type::Vec3I& return_blockPosition);

			// #include "raycast.declare.h"
		}
	}

} // namespace VoxelFrame
