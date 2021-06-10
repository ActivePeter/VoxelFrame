class Graph;

////////////////////////////////////////////////////////
#ifndef ___GRAPH_H__
#define ___GRAPH_H__
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "base.h"
#include "Mesh.h"
#include "game/chunk.h"
#include "camera.h"
#include "gui/_gui.h"
#include "shader_m.h"
#include "texture.h"

////////////////////////

class Graph
{
private:
    /* data */
    void drawMesh();

public:
    std::shared_ptr<Gui> _guiPtr;
    std::shared_ptr<TextureManager> _textureManagerPtr;
    int windowH = 800;
    int windowW = 1000;
    GLFWwindow *window;
    float highDPIscaleFactor = 1;
    std::shared_ptr<Camera> cameraPtr;
    std::shared_ptr<Shader> camShaderPtr;

    // timing
    // float deltaTime = 0.0f; // time between current frame and last frame
    // float lastFrame = 0.0f;
    //用于遍历并绘制所有网格
    //玩家区块变更就需要更新这个列表
    std::vector<std::shared_ptr<Chunk>> chunks2Draw;
    void addChunk2DrawList(std::shared_ptr<Chunk> chunkPtr);

    void doDraw();
    bool init();
    inline void drawBegin();
    inline void drawEnd();

    inline bool running()
    {
        return !glfwWindowShouldClose(window);
    }
    inline void end()
    {
        glfwTerminate();
    }
};

// extern Graph _g_Graph;

// #endif // __DRAWSYS_H__
#endif // ___GRAPH_H__