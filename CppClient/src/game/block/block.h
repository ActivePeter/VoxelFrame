namespace VoxelFrame
{
	namespace _Game
	{
		namespace _Block
		{
			class Manager;
			// class CommonBlockMesh;
			class Info;
		}
	}
}
#ifndef __BLOCK_H__
#define __BLOCK_H__
namespace VoxelFrame
{
	namespace _Game
	{
		namespace _Block
		{
			enum class FaceDirection
			{
				X_Positive = 0,
				X_Negative,
				Y_Positive,
				Y_Negative,
				Z_Positive,
				Z_Negative,
				End,
			};
		}
	}
}
#include "base/vf_base.h"

#include "blocks_registry.h"
#include "graph/Mesh.h"

// #include "enum.h"
#include "physic_engine/physic_engine.h"
/**
 * 即最普通的方块状态，撑满一格
*/
#include "blocks_mesh/_BlockMesh_Base.h"

#include "blocks_uv_setter/_BlockUVSetter_Base.h"
namespace VoxelFrame
{
	namespace _Game
	{
		namespace _Block
		{
			// #pragma once

			// class CommonBlockMeshModel
			// {
			// private:
			//     int []
			//     /* data */
			// public:
			// };

			//标准顺序

			// uint32_t _0_0_0 = getIndexByPos(x + 0, y + 0, z + 0);
			// uint32_t _1_0_0 = getIndexByPos(x + 1, y + 0, z + 0);
			// uint32_t _0_1_0 = getIndexByPos(x + 0, y + 1, z + 0);
			// uint32_t _0_0_1 = getIndexByPos(x + 0, y + 0, z + 1);
			// uint32_t _1_1_0 = getIndexByPos(x + 1, y + 1, z + 0);
			// uint32_t _0_1_1 = getIndexByPos(x + 0, y + 1, z + 1);
			// uint32_t _1_0_1 = getIndexByPos(x + 1, y + 0, z + 1);
			// uint32_t _1_1_1 = getIndexByPos(x + 1, y + 1, z + 1);
			//

			///////////////////////////

			class Manager;

			/**
				存储所有方块信息，
				若empty，则uvsetter和blockmesh是没有的
			*/
			class Info
			{
				friend class Manager;

				bool isEmptyBlockFlag = false;

			public:
				std::shared_ptr<BlockUVSetter_Base> blockUVSetter;
				std::shared_ptr<BlockMesh_Base> blockMesh;
				/**
	 * 判断是否为空方快
	*/
				bool isEmptyBlock()
				{
					return isEmptyBlockFlag;
				}
				static Info newEmptyBlock()
				{
					Info Info;
					Info.isEmptyBlockFlag = true;
					return Info;
				}

				/**
	 * 默认构造函数
	*/
				Info()
				{
				}

				/*
		模板构造函数
	*/
				template <typename BlockUVSetterType, typename BlockMeshType>
				Info(std::shared_ptr<BlockUVSetterType> blockUVSetter, std::shared_ptr<BlockMeshType> blockMesh)
				{
					this->blockUVSetter = blockUVSetter; // static_cast<BlockUVSetter_Base>(blockUVSetter);
					this->blockMesh = blockMesh;
					//static_cast<BlockMesh_Base>(blockMesh);
				}
			};

			class Manager
			{
			private:
				/**
	 * 以方块id的顺序存储方块信息，可以快速的随机访问
	*/
				std::vector<Info> Infos;

			public:
				/**
	 * block manager构造函数
	*/
				Manager();

				/**
	 * 添加block信息（在注册block时调用
	*/
				void addBlock(const Info& Info)
				{
					Infos.push_back(Info);
				}

				/**
	 * 添加一个emptyblock（在注册block时调用
	*/
				void addEmptyBlock(const Info& Info)
				{
					Infos.push_back(Info);
					//设置为空方块属性
					Infos.end()->isEmptyBlockFlag = true;
				}
				/**
	 * 根据blockId获取Info
	*/
				Info& getInfo(int blockId)
				{
					return Infos[blockId];
				}
			};
			void pushOneFace2Mesh(int blockx, int blocky, int blockz, Info& Info, _Block::FaceDirection dir, _Graph::Mesh& mesh);
		}
	}
}
#endif // __BLOCK_H__