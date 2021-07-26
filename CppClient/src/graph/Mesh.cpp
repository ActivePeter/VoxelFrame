#include "Mesh.h"
namespace VoxelFrame
{
	namespace _Graph
	{
		void Mesh::draw()
		{
			setupMesh();

			if (inited)
			{
				bindTexture();
				glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
			}
		}

		void Mesh::setupMesh()
		{
			//这里需要mutex
			// dataMut.lock();
			if (needSetupBeforeDraw)
			{
				if (!inited)
				{
					setupResourceTest();
					glGenVertexArrays(1, &VAO);
					glGenBuffers(1, &VBO);
					glGenBuffers(1, &EBO);
					inited = true;
				}
				// create buffers/arrays

				glBindVertexArray(VAO);
				// // load data into vertex buffers
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				// // A great thing about structs is that their memory layout is sequential for all its items.
				// // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
				// // again translates to 3/2 floats which translates to a byte array.
				dataMut.lock();
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
				dataMut.unlock();

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				dataMut.lock();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
				dataMut.unlock();
				// // set the vertex attribute pointers
				// // vertex Positions

				//坐标 对齐
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
				glEnableVertexAttribArray(0);

				//uv 对齐
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);

				// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				needSetupBeforeDraw = false;
			}

			if (inited)
			{
				glBindVertexArray(VAO);
				// // load data into vertex buffers
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				//坐标 对齐
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
				glEnableVertexAttribArray(0);

				//uv 对齐
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(glm::vec3)));
				glEnableVertexAttribArray(1);
			}
		}
	}
}