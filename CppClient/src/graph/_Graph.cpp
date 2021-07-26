// #include "DrawSys.h"
// #include "glad/glad.h"

#include "_Graph.h"

//#include "GLFW/glfw3.h"
#include <iostream>
// #include "io/Input.h"
// #include "system/io/_IO.h"
#include "system_related/_Input.h"
#include "./gui/_gui.h"
#include "game/chunk/chunk_manager.h"
#include "graph/shader_m.h"

namespace VoxelFrame
{
	namespace _Graph
	{
		struct RaycastDraw {
			/*const char* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0";*/
				/*const char* fragmentShaderSource = "#version 330 core\n"
					"out vec4 FragColor;\n"
					"void main()\n"
					"{\n"
					"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
					"}\n\0";*/
			const char* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"uniform mat4 view;\n"
				"uniform mat4 projection;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = projection*view * vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
				"}\0";
			const char* fragmentShaderSource = "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\n\0";
			bool inited = false;
			unsigned int VBO;
			unsigned int VAO;
			//unsigned int shaderProgram;

			std::shared_ptr<Shader> shader;
			void drawRaycastLine(const glm::mat4& projection, const glm::mat4& view, Type::Vec3F p1, Type::Vec3I p2)
			{
				float vertices[9] = {
					/*p1.x,p1.y,p1.z,
					p2.x,p2.y,p2.z,
					p1.x,p1.y,p1.z*/
					// first triangle
					//-0.9f, -0.5f, 0.0f, // left
					//-0.0f, -0.5f, 0.0f, // right
					//-0.45f, 0.5f, 0.0f, // top
										// second triangle
					0.0f, -0.5f, 0.0f,	// left
					0.9f, -0.5f, 0.0f,	// right
					//0.45f, 0.5f, 0.0f	// top
					//p1.x,p1.y,p1.z
				};
				vertices[3] = p1.x;
				vertices[4] = p1.y + 0.1;
				vertices[5] = p1.z;

				vertices[0] = vertices[6] = p2.x + 0.5;
				vertices[1] = vertices[7] = p2.y + 1;
				vertices[2] = vertices[8] = p2.z + 0.5;
				if (!inited)
				{
					inited = true;
					shader = std::make_shared<Shader>(false, vertexShaderSource, fragmentShaderSource);
					//{
					//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
					//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
					//	glCompileShader(vertexShader);
					//	// check for shader compile errors
					//	int success;
					//	char infoLog[512];
					//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
					//	if (!success)
					//	{
					//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
					//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
					//	}
					//	// fragment shader
					//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
					//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
					//	glCompileShader(fragmentShader);
					//	// check for shader compile errors
					//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
					//	if (!success)
					//	{
					//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
					//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
					//	}
					//	// link shaders
					//	shaderProgram = glCreateProgram();
					//	glAttachShader(shaderProgram, vertexShader);
					//	glAttachShader(shaderProgram, fragmentShader);
					//	glLinkProgram(shaderProgram);
					//	// check for linking errors
					//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
					//	if (!success) {
					//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
					//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
					//	}
					//	glDeleteShader(vertexShader);
					//	glDeleteShader(fragmentShader);
					//}


					// unsigned int VBO, VAO;
					glGenVertexArrays(1, &VAO);
					glGenBuffers(1, &VBO);
					// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).



					glBindVertexArray(VAO);

					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
					glEnableVertexAttribArray(0);

					// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
					glBindBuffer(GL_ARRAY_BUFFER, 0);

					// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
					// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
					glBindVertexArray(0);
				}

				//glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);/*

				//glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);*/
				/*
				shader->setMat4("projection", projection);

				//// camera/view transformation
				////glm::mat4 view = camera.GetViewMatrix();
				shader->setMat4("view", view);

				//
				shader->use();
				*/

				//float vertices[] = {
				//	// first triangle
				//	-0.9f, -0.5f, 0.0f, // left
				//	-0.0f, -0.5f, 0.0f, // right
				//	-0.45f, 0.5f, 0.0f, // top
				//						// second triangle
				//	0.0f, -0.5f, 0.0f,	// left
				//	0.9f, -0.5f, 0.0f,	// right
				//	0.45f, 0.5f, 0.0f	// top
				//};

				glBindVertexArray(VAO);

				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

				shader->use();
				shader->setMat4("projection", projection);

				// camera/view transformation
				//glm::mat4 view = camera.GetViewMatrix();
				shader->setMat4("view", view);
				//glUseProgram(shaderProgram);


				//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
		};
		RaycastDraw raycastDraw;

		// #include "Models/WindowInfoModel.h"
		// Graph _g_Graph;

		// float deltatime = 0.0f;
		// float lastframe = 0.0f;
		// float lastX = 400, lastY = 300;
		// float sensitivity = 0.05f;

		// void drawBegin();
		// // void drawMain();
		// void drawEnd();
		// void processInput(GLFWwindow *window, int key, int scancode, int action, int mode);
		// void mouse_callback(GLFWwindow *window, double xpos, double ypos);

		//////////////////////////////////////
		//
		// 生命周期
		//
		//////////////////////////////////////

		//暂时test
		//float vertices[] = {
		//	-0.5f, -0.5f, 0.0f, // left
		//	0.5f, -0.5f, 0.0f,	// right
		//	0.0f, 0.5f, 0.0f	// top
		//};
		//unsigned int VBO, VAO;

		bool Graph::init()
		{
			// glfwInit(); //初始化GLFW
			//指明OpenGL版本
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
			// float highDPIscaleFactor = 1.0;
			// #ifdef _WIN32
			// if it's a HighDPI monitor, try to scale everything

			// 适配高分屏 ///////////////////////////////////////////////////
			// GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			// float xscale, yscale;
			// glfwGetMonitorContentScale(monitor, &xscale, &yscale);
			// if (xscale > 1 || yscale > 1)
			// {
			//     this->highDPIscaleFactor = xscale;
			//     glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
			// }
			// else
			{
				this->highDPIscaleFactor = 1;
			}
			////////////////////////////////////////////////////////////////

			// 创建窗口 /////////////////////////////////////////////////////
			this->gameWindow.createWindow();

			//监听窗口大小变化
			_guiPtr = std::make_shared<Gui>();
			_guiPtr->init();

			_textureManagerPtr = std::make_shared<TextureManager>();

			//camera
			cameraPtr = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
			camShaderPtr = std::make_shared<Shader>("camera.vs", "camera.fs");

			//暂时test ////////////////////

			// glGenVertexArrays(1, &VAO);
			// glGenBuffers(1, &VBO);
			// // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			// glBindVertexArray(VAO);

			// glBindBuffer(GL_ARRAY_BUFFER, VBO);
			// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
			// glEnableVertexAttribArray(0);

			// // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			// glBindBuffer(GL_ARRAY_BUFFER, 0);

			// // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			// glBindVertexArray(0);
			////////////////
			return true;
		}

		///////////////////////////////////////////////////////////////////////

		// 绘制相关 /////////////////////////////////////////////////////////
		void Graph::drawMesh()
		{
			auto& camShader = *camShaderPtr;
			auto& camera = *cameraPtr;

			// 仅绘制边线模式
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			// 相机操作
			camShader.use();
			// glUseProgram(shaderProgram);

			// pass projection matrix to shader (note that in this case it could change every frame)
			glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()),
				(float)gameWindow.windowW / (float)gameWindow.windowH, 0.1f,
				100.0f);
			camShader.setMat4("projection", projection);

			// camera/view transformation
			glm::mat4 view = camera.GetViewMatrix();
			camShader.setMat4("view", view);

			//_textureManagerPtr->bindChunkTexture();

			/*for (auto& i : App::getInstance().gamePtr->chunkManager->chunks2Draw)
			{
				for (auto j : meshes2draw)
				{
					if (i.get() == j)
					{
						j->draw();
					}
				}
			}*/
			for (auto iter = meshes2draw.begin(); iter != meshes2draw.end(); iter++)
			{
				//iter.draw();
				(*iter)->draw();
			}
			//drawRaycastLine();
			auto player = App::getInstance().gamePtr->mainPlayer;
			if (player) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				raycastDraw.drawRaycastLine(projection, view, camera.getPosition(), player->mainPlayerWorldOperator.blockSelector.position);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}

		// void Graph::addChunk2DrawList(std::shared_ptr<Chunk> chunkPtr)
		// {

		//     chunks2Draw.push_back(chunkPtr);
		//     chunkPtr->constructMesh();
		// }

		void Graph::doDraw()
		{
			drawBegin();

			// glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			// glDrawArrays(GL_TRIANGLES, 0, 3);

			// glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowW / (float)windowH, 0.1f, 100.0f);
			// camShader.setMat4("projection", projection);
			// // camera / view transformation
			// glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			// float radius = 10.0f;
			// float camX = sin(glfwGetTime()) * radius;
			// float camZ = cos(glfwGetTime()) * radius;
			// view = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(-1, -1, -1), glm::vec3(0.0f, 1.0f, 0.0f));
			// camShader.setMat4("view", view);

			drawMesh();
			_guiPtr->renderGui();
			_guiPtr->drawGui(); //绘制gui，最后一步做
			drawEnd();
		}

		inline void Graph::drawBegin()
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// 开启面剔除
			// glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			// glCullFace(GL_FRONT);
		}

		inline void Graph::drawEnd()
		{
			SDL_GL_SwapWindow(gameWindow.window);
			//将存储在缓冲区中的像素颜色进行绘制，这里涉及到双缓冲的问题
			// glfwSwapBuffers(gameWindow.window);
			//检查有没有触发什么事件（键盘输入、鼠标移动等)、窗口改变
			// glfwPollEvents();
			// glfwSetKeyCallback(_Graph.window, processInput);
			// glfwSetCursorPosCallback(_Graph.window, mouse_callback);
		}
	}
}