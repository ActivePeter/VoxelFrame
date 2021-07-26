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
			Vertex(const Type::Vec3F &pos)
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

			void appendVetexPoses(const std::vector<Type::Vec3F> &vertexPoses)
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
			// 绘制网格
			void draw();

			//初始化网格(在绘制中调用
			void setupMesh();

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