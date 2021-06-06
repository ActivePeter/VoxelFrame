#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <Datadef/data.h>
using namespace std;

namespace DrawSys
{
    class MapDrawer
    {
    private:
        const char *vsPath = "./resource/Shader/shader.vs";
        const char *fsPath = "./resource/Shader/shader.fs";
        unsigned int VBO, VAO, EBO, shaderProgram;
        unsigned int textures[6];
        const float vertices[180] =
            {
                0.5f,
                -0.5f,
                0.5f,
                0.0f,
                0.0f, //正面
                -0.5f,
                -0.5f,
                0.5f,
                1.0f,
                0.0f,
                -0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,

                -0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,
                0.5f,
                0.5f,
                0.5f,
                0.0f,
                1.0f,
                0.5f,
                -0.5f,
                0.5f,
                0.0f,
                0.0f,

                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f, //反面
                0.5f,
                0.5f,
                -0.5f,
                1.0f,
                0.0f,
                0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                1.0f,

                0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                1.0f,
                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                1.0f,
                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f,

                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f, //左面
                -0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                0.0f,
                -0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,

                -0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                0.5f,
                0.0f,
                1.0f,
                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f,

                0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f, //右面
                0.5f,
                0.5f,
                0.5f,
                1.0f,
                0.0f,
                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,

                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,
                0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                1.0f,
                0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f,

                0.5f,
                0.5f,
                0.5f,
                0.0f,
                0.0f, //上面
                0.5f,
                0.5f,
                -0.5f,
                1.0f,
                0.0f,
                -0.5f,
                0.5f,
                -0.5f,
                1.0f,
                1.0f,

                -0.5f,
                0.5f,
                -0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                0.5f,
                0.0f,
                1.0f,
                0.5f,
                0.5f,
                0.5f,
                0.0f,
                0.0f,

                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f, //下面
                0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                0.0f,
                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,

                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                -0.5f,
                0.5f,
                0.0f,
                1.0f,
                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
        };

    public:
        MapDrawer(/* args */);
        static MapDrawer *getInstance();
        unsigned int LoadTexture(string path);
        void AddShader(GLuint ShaderProgram, const char *ShaderText, GLenum ShaderType);
        void CompileShaders();
        bool ReadFile(const char *pFileName, string &outFile);
        float *GenerateVertices(float x, float y, float z);
        void doDraw();
        void DrawCube(glm::vec3 offset);
        void DrawChunk(ChunkModel data, glm::vec3 pos);
        void UpdateView(float xoffset, float yoffset);
    };

} // namespace DrawSys

#endif // __MAPDRAWER_H__