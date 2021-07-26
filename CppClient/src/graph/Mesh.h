struct Vertex;
struct Texture;
class Mesh;
////////////////////////////

#ifndef __MESH_H__
#define __MESH_H__

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include <learnopengl/shader.h>
#include "base/vf_base.h"

#include <string>
#include <vector>
#include <mutex>
#include <atomic>
// #include "game/chunk/chunk.h"
// using namespace std;
// using VertexPos = glm::vec3;

namespace VoxelFrame
{
	namespace _Graph
	{
		// using VertexPoses = std::vector<Type::Vec3F>;
		//one point of triangle and uv info
		struct Vertex
		{
			// // position
			Type::Vec3F Position;

			// // texCoords材质uv
			glm::vec2 TexCoords;

			// // normal
			// glm::vec3 Normal;

			// // tangent
			// glm::vec3 Tangent;
			// // bitangent
			// glm::vec3 Bitangent;
			Vertex() {}
			Vertex(const Type::Vec3F& pos)
			{
				this->Position = pos;
			}
			void setUV(float u, float v)
			{
				TexCoords.x = u;
				TexCoords.y = v;
			}
			void setPosition(float x, float y, float z)
			{
				Position = glm::vec3(x, y, z);
			}
			void addPosition(float x, float y, float z)
			{
				Position.x += x;
				Position.y += y;
				Position.z += z;
			}
		};

		struct Texture
		{
			unsigned int id;
			std::string type;
			std::string path;
		};
		using Vertices = std::vector<Vertex>;
		using Indices = std::vector<unsigned int>;
		class Mesh
		{
		public:
			std::mutex dataMut;

			// mesh Data

			Vertices vertices;
			Indices indices;

			std::vector<Texture> textures;
			glm::vec3 mesh_position;
			unsigned int VAO;

			std::atomic<int> indicesSize;
			std::atomic<bool> needSetupBeforeDraw;
			bool constructed = false;

			Mesh() : needSetupBeforeDraw(false), indicesSize(0)
			{
			}

			void appendVetexPoses(const std::vector<Type::Vec3F>& vertexPoses)
			{
				// vertices.resize(vertices.size() + vertexPoses.size());
				for (int i = 0; i < vertexPoses.size(); i++)
				{
					vertices.push_back(Vertex(vertexPoses[i]));
				}
			}
			// constructor
			// Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
			// {
			//     this->vertices = vertices;
			//     this->indices = indices;
			//     this->textures = textures;

			//     // now that we have all the required data, set the vertex buffers and its attribute pointers.
			//     setupMesh();
			// }
			// void expandIndices(size_t size)
			// {
			//     for (int i = 0; i < size; i++)
			//     {
			//         indices.push_back(0);
			//     }
			// }
			virtual void bindTexture() = 0;
			// render the mesh
			void draw();

			void setupMesh()
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
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
					glEnableVertexAttribArray(0);

					//uv 对齐
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
					glEnableVertexAttribArray(1);

					// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
					needSetupBeforeDraw = false;
				}

				if (inited) {
					glBindVertexArray(VAO);
					// // load data into vertex buffers
					glBindBuffer(GL_ARRAY_BUFFER, VBO);

					//坐标 对齐
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
					glEnableVertexAttribArray(0);

					//uv 对齐
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
					glEnableVertexAttribArray(1);
				}

			}

		private:
			// render data
			unsigned int VBO, EBO;
			bool inited = false;
			// const char *vertexShaderSource = "#version 330 core\n"
			//                                  "layout (location = 0) in vec3 aPos;\n"
			//                                  "void main()\n"
			//                                  "{\n"
			//                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			//                                  "}\0";
			// const char *fragmentShaderSource = "#version 330 core\n"
			//                                    "out vec4 FragColor;\n"
			//                                    "void main()\n"
			//                                    "{\n"
			//                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			//                                    "}\n\0";
			// unsigned int shaderProgram;
			// initializes all the buffer objects/arrays
			void setupResourceTest()
			{
				// // vertex shader
				// unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
				// glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
				// glCompileShader(vertexShader);
				// // check for shader compile errors
				// int success;
				// char infoLog[512];
				// glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
				// if (!success)
				// {
				//     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				//     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				//               << infoLog << std::endl;
				// }
				// // fragment shader
				// unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				// glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
				// glCompileShader(fragmentShader);
				// // check for shader compile errors
				// glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
				// if (!success)
				// {
				//     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				//     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				//               << infoLog << std::endl;
				// }
				// // link shaders
				// shaderProgram = glCreateProgram();
				// glAttachShader(shaderProgram, vertexShader);
				// glAttachShader(shaderProgram, fragmentShader);
				// glLinkProgram(shaderProgram);
				// // check for linking errors
				// glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
				// if (!success)
				// {
				//     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				//     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				//               << infoLog << std::endl;
				// }
				// glDeleteShader(vertexShader);
				// glDeleteShader(fragmentShader);
			}
		};
	}
}
#endif // __MESH_H__