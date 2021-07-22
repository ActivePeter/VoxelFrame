#include "BlockMesh_Common.h"
namespace VoxelFrame
{
    namespace _Game
    {
        namespace _Block
        {
            // 不同种类的网格信息，表达在不同文件里，比较清晰
            void BlockMesh_Common::setFaceVertexPosOnDir(std::vector<Type::Vec3F> &vertexPoses, _Block::FaceDirection dir)
            {
                // 8个点 对应8个索引
                switch (dir)
                {
                case _Block::FaceDirection::X_Positive:
                    // 1 4 7 6
                    setFaceVertices(vertexPoses, 1, 4, 7, 6);
                    break;
                case _Block::FaceDirection::X_Negative:
                    // 3 5 2 0
                    setFaceVertices(vertexPoses, 3, 5, 2, 0);
                    break;
                case _Block::FaceDirection::Y_Positive:
                    // 2 5 7 4
                    setFaceVertices(vertexPoses, 2, 5, 7, 4);
                    break;
                case _Block::FaceDirection::Y_Negative:
                    // 1 6 3 0
                    setFaceVertices(vertexPoses, 1, 6, 3, 0);
                    break;
                case _Block::FaceDirection::Z_Positive:
                    // 6 7 5 3
                    setFaceVertices(vertexPoses, 6, 7, 5, 3);
                    break;
                case _Block::FaceDirection::Z_Negative:
                    // 0 2 4 1
                    setFaceVertices(vertexPoses, 0, 2, 4, 1);
                    break;

                default:
                    std::cout << "no face enum matched" << std::endl;
                    break;
                }
            }

            void BlockMesh_Common::addUpStandardVertexOfIndex(Type::Vec3F &vertexPos, uint8_t index)
            {
                switch (index)
                {
                // case 0: nothing need to do
                //     vertex.addPosition(0,0,0);
                //     break;
                case 1:
                    vertexPos += Type::Vec3F(1, 0, 0);
                    //vertex.addPosition(1, 0, 0);
                    break;
                case 2:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(0, 1, 0);

                    break;
                case 3:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(0, 0, 1);
                    break;
                case 4:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(1, 1, 0);
                    break;
                case 5:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(0, 1, 1);
                    break;
                case 6:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(1, 0, 1);
                    break;
                case 7:
                    //vertex.addPosition(
                    vertexPos += Type::Vec3F(1, 1, 1);
                    break;
                }
            }

            //这个应该可以拿到Base去
            void BlockMesh_Common::getBlockValidTriangles(std::vector<Type::Vec3F> &vertexPoses, _Graph::Indices &indices)
            {
                for (int a = 0; a < (int)(_Block::FaceDirection::End); a++)
                {
                    this->pushOneFaceVerticesAndIndices_selfPos((_Block::FaceDirection)a, vertexPoses, indices, 0);
                }
            }
            //这个应该也可以拿到Base去
            // void BlockMesh_Common::pushOneFace2Mesh(int blockx, int blocky, int blockz, _Block::FaceDirection dir, Mesh &mesh)
            // {
            //     {
            //         // printf("dir: %d \r\n", dir);
            //         //Vertex vertex;
            //         //添加方块坐标和区块坐标（网格坐标）的偏移
            //         //vertex.setPosition(mesh.mesh_position.x + blockx,
            //         //mesh.mesh_position.y + blocky,
            //         //mesh.mesh_position.z + blockz);
            //         //加入序列
            //         //for (int i = 0; i < 4; i++)
            //         //{
            //         //mesh.vertices.push_back(vertex);
            //         //}
            //         //这一块要为了后续程序统一做出整改
            //         // 构造网格时传入一个空vector<VertexPos>（临时
            //         // 构造过程中往vector填入内容，
            //         // 最后构造结束后再把数据拷贝到vertex数组里
            //         VertexPoses poses;
            //         this->pushOneFaceVerticesAndIndices_selfPos(dir, poses, mesh.indices);
            //         //加上网格以及方块的坐标，转换到世界坐标上
            //         for (auto &i : poses)
            //         {
            //             i += VertexPos(
            //                 mesh.mesh_position.x + blockx,
            //                 mesh.mesh_position.y + blocky,
            //                 mesh.mesh_position.z + blockz);
            //         }
            //         mesh.appendVetexPoses(poses);
            //         // this->setVertexUVOnDir(dir, mesh);
            //         blockUVSetter->setVertexUVOnDir(dir, mesh);

            //         // printf("%d %d\r\n", mesh.vertices.size(), mesh.indices.size());
            //     }
            // }

            //这个拿不了

            void BlockMesh_Common::pushOneFaceVerticesAndIndices_selfPos(_Block::FaceDirection dir,
                                                                         std::vector<Type::Vec3F> &vertexPoses,
                                                                         _Graph::Indices &indices, unsigned int vertexIndexOffset)
            {
                setFaceVertexPosOnDir(vertexPoses, dir);
                //三角形点序号，对应刚添加的四个点
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 4));
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 3));
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 2));
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 4));
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 2));
                indices.push_back(vertexIndexOffset + (unsigned int)(vertexPoses.size() - 1));
            }
        }
    }
}
