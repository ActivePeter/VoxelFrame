class Graph;

////////////////////////////////////////////////////////
#ifndef ___GRAPH_H__
#define ___GRAPH_H__
#include "system_related/_media_api.h"
// #include "GLFW/glfw3.h"
#include "vf_base.h"
#include "Mesh.h"
#include "game/chunk.h"
#include "camera.h"
#include "gui/_gui.h"
#include "shader_m.h"
#include "texture.h"
#include "system_related/GameWindow.h"
class Graph
{
private:
    /* data */
    void drawMesh();

public:
    bool runningFlag = true;
    std::shared_ptr<Gui> _guiPtr;
    std::shared_ptr<TextureManager> _textureManagerPtr;

    float highDPIscaleFactor = 1;
    bool mouseIsLocked = false;
    std::shared_ptr<Camera> cameraPtr;
    std::shared_ptr<Shader> camShaderPtr;
    GameWindow gameWindow;
    // timing
    // float deltaTime = 0.0f; // time between current frame and last frame
    // float lastFrame = 0.0f;

    // void addChunk2DrawList(std::shared_ptr<Chunk> chunkPtr);

    void doDraw();
    bool init();
    inline void drawBegin();
    inline void drawEnd();

    inline bool running()
    {
        return runningFlag;
    }
    inline void end()
    {
        SDL_GL_DeleteContext(gameWindow.GLContext);
        SDL_DestroyWindow(gameWindow.window);
        SDL_Quit();
        // glfwTerminate();
    }
};

// extern Graph _g_Graph;

// #endif // __DRAWSYS_H__
#endif // ___GRAPH_H__