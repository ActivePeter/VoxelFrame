#include "Mesh.h"
#include "game/chunk/chunk.h"

namespace VoxelFrame
{
	namespace _Graph
	{
		void Mesh::draw()
		{
			{
				// std::cout << "chunk on draw" << std::endl;
				// Shader &shader;
				// // bind appropriate textures
				// unsigned int diffuseNr = 1;
				// unsigned int specularNr = 1;
				// unsigned int normalNr = 1;
				// unsigned int heightNr = 1;
				// for (unsigned int i = 0; i < textures.size(); i++)
				// {
				//     glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				//     // retrieve texture number (the N in diffuse_textureN)
				//     string number;
				//     string name = textures[i].type;
				//     if (name == "texture_diffuse")
				//         number = std::to_string(diffuseNr++);
				//     else if (name == "texture_specular")
				//         number = std::to_string(specularNr++); // transfer unsigned int to stream
				//     else if (name == "texture_normal")
				//         number = std::to_string(normalNr++); // transfer unsigned int to stream
				//     else if (name == "texture_height")
				//         number = std::to_string(heightNr++); // transfer unsigned int to stream

				//     // now set the sampler to the correct texture unit
				//     glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
				//     // and finally bind the texture
				//     glBindTexture(GL_TEXTURE_2D, textures[i].id);
				// }

				// // draw mesh
				// glUseProgram(shaderProgram);
				// if (inited && dataMut.try_lock())
				// {

				//if (needSetupBeforeDraw)
				{
					// dataMut.unlock();
					setupMesh();

					/*auto chunkPtr = (VF::_Game::_Chunk::Chunk*)this;
					printf("chunk is setup %d %d %d iv:%d %d %.2f %.2f %.2f\r\n", chunkPtr->key.x, chunkPtr->key.y, chunkPtr->key.z, indices.size(), vertices.size(),
						vertices[0].Position.x, vertices[0].Position.y, vertices[0].Position.z);*/
				}
				if (inited)
				{
					/*auto chunkPtr = (VF::_Game::_Chunk::Chunk*)this;
					printf("chunk is drawing %d %d %d iv:%d %d %.2f %.2f %.2f\r\n", chunkPtr->key.x, chunkPtr->key.y, chunkPtr->key.z, indices.size(), vertices.size(),
						vertices[0].Position.x, vertices[0].Position.y, vertices[0].Position.z);*/
					bindTexture();
					//如果锁成功了
					// dataMut.lock();

					// dataMut.lock();
					int sizeCopy = indicesSize;
					// dataMut.unlock();
					//App::
					//glBindVertexArray(VAO);
					//glBindVertexArray(VAO);
					//// // load data into vertex buffers
					//glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
				}
				else
				{
					//std::cout << "mesh not inited when draw called" << std::endl;
				}

				//解锁

				// }
				// glBindVertexArray(0); // no need to unbind it every time

				// // always good practice to set everything back to defaults once configured.
				// glActiveTexture(GL_TEXTURE0);
			}
		}
	}
}