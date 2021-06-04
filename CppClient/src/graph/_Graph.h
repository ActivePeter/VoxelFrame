#ifndef __DRAWSYS_H__
#define __DRAWSYS_H__
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "base.h"
#include "Mesh.h"
#include "game/chunk.h"

class Chunk;
////////////////////////

class Graph
{
private:
    /* data */
    void drawMesh();

public:
    int windowH = 800;
    int windowW = 1000;
    GLFWwindow *window;
    float highDPIscaleFactor = 1;

    //用于遍历并绘制所有网格
    //玩家区块变更就需要更新这个列表
    std::vector<std::shared_ptr<Chunk>> chunks2Draw;
    void addChunk2DrawList(std::shared_ptr<Chunk> chunkPtr);

    void doDraw();
    bool init();
    inline bool running()
    {
        return !glfwWindowShouldClose(window);
    }
    inline void end()
    {
        glfwTerminate();
    }
};

extern Graph _g_Graph;

#endif // __DRAWSYS_H__