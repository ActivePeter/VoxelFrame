// #include "DrawSys.h"
// #include "glad/glad.h"

#include "_Graph.h"

// #include "GLFW/glfw3.h"
#include <iostream>
// #include "io/Input.h"
// #include "system/io/_IO.h"
#include "system_related/_Input.h"
#include "./gui/_gui.h"
#include "game/chunk/chunk_manager.h"


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
float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left
	0.5f, -0.5f, 0.0f,  // right
	0.0f, 0.5f, 0.0f    // top
};
unsigned int VBO, VAO;

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
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 相机操作
	camShader.use();
	// glUseProgram(shaderProgram);

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)gameWindow.windowW / (float)gameWindow.windowH, 0.1f, 100.0f);
	camShader.setMat4("projection", projection);

	// camera/view transformation
	glm::mat4 view = camera.GetViewMatrix();
	camShader.setMat4("view", view);

	//_textureManagerPtr->bindChunkTexture();

	for (auto i : meshes2draw)
	{
		i->draw();
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
// inline void drawBegin()
// {
//     // float currenttime = (float)glfwGetTime();
//     // deltatime = currenttime - lastframe;
//     // lastframe = currenttime;

//     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     // 开启面剔除
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_FRONT);
// }

// inline void drawMain()
// {
//     // if (GuiSys::isRender)
//     // {
//     // MapDrawer::getInstance()->doDraw();
//     // }

//     //绘制chunk网格

// }

// inline void drawEnd()
// {
//     //将存储在缓冲区中的像素颜色进行绘制，这里涉及到双缓冲的问题
//     glfwSwapBuffers(_g_Graph.window);
//     //检查有没有触发什么事件（键盘输入、鼠标移动等)、窗口改变
//     glfwPollEvents();
//     // glfwSetKeyCallback(_Graph.window, processInput);
//     // glfwSetCursorPosCallback(_Graph.window, mouse_callback);
// }
//////////////////////////////////////////////////////////////////////////////////////////////////

// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     //     float xoffset = (float)(xpos - lastX);
//     //     float yoffset = (float)(lastY - ypos);
//     //     lastX = (float)xpos;
//     //     lastY = (float)ypos;
//     //     xoffset *= sensitivity;
//     //     yoffset *= sensitivity;
//     //     MapDrawer::getInstance()->UpdateView(xoffset, yoffset);
//     // }
// }
// void processInput(GLFWwindow *window, int key, int scancode, int action, int mode)
// {
//     //     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     //         glfwSetWindowShouldClose(window, true);
//     //     if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Forward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Leftward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Backward(deltatime*20.0f);
//     //     if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
//     //         MapDrawer::getInstance()->Rightward(deltatime*20.0f);
//     // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//     //     MapDrawer::getInstance()->UpdateView(0.01f, 0.01f);
// }
