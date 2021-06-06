// #include "glad/glad.h"

#include "MapDrawer.h"
#include "iostream"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "string"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stdio.h"
#include <fstream>
#include "Camera.h"
#define BLOCKSIZE 1.0f

namespace DrawSys
{
    using namespace std;
    MapDrawer::MapDrawer(/* args */)
    {
        shaderProgram = glCreateProgram();
        if (shaderProgram == 0)
        {
            fprintf(stderr, "Error creating shader program\n");
            exit(1);
        }
        CompileShaders();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO); //顶点缓冲对象

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // glBindVertexArray(VAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(shaderProgram, "mainTex"), 0);
        Camera::GetInstance().LookAt(shaderProgram, Camera::GetInstance().GetCameraTarget());
        Camera::GetInstance().SetViewRange(shaderProgram, 60.0f, 800.0f, 600.0f);
        //glEnable(GL_CULL_FACE);
        for (int i = 1; i <= 6; i++)
        {
            char path[30];
            sprintf_s(path, "./resource/images/%d.png", i);
            textures[i - 1] = LoadTexture(path);
        }
    }

    MapDrawer *MapDrawer::getInstance()
    {
        static MapDrawer mp;
        return &mp;
    }

    void MapDrawer::doDraw()
    {
        // glm::mat4 rotate = glm::mat4(1.0f);
        // rotate = glm::rotate(rotate, 1.0f*(float)glfwGetTime() , glm::vec3(1.0f, 1.0f, 0.0f));
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotate"), 1, GL_FALSE, glm::value_ptr(rotate));

        // glm::vec3 offset=glm::vec3(0.0f,0.0f,0.0f);
        // glUniform3fv(glGetUniformLocation(shaderProgram,"offset"),1,glm::value_ptr(offset));
        // float x=(float)sin(glfwGetTime())*1.0f;
        // float z=(float)cos(glfwGetTime())*1.0f;
        // camera.LookAt(shaderProgram,glm::vec3(0.0f,0.0f,0.0f));
        // camera.SetViewRange(shaderProgram,60.0f,800.0f,600.0f);
        // DrawCube(glm::vec3(0.5f,0.5f,0.0f));
        // DrawCube(glm::vec3(-0.5f,-0.5f,0.0f));
        DrawCube(glm::vec3(0.0f, 0.0f, 0.0f));

        DrawCube(glm::vec3(1.0f, 0.0f, 0.0f));
        DrawCube(glm::vec3(-1.0f, 0.0f, 0.0f));
        DrawCube(glm::vec3(0.0f, 0.0f, 1.0f));
        DrawCube(glm::vec3(0.0f, 0.0f, -1.0f));

        DrawCube(glm::vec3(1.0f, 0.0f, 1.0f));
        DrawCube(glm::vec3(-1.0f, 0.0f, 1.0f));
        DrawCube(glm::vec3(1.0f, 0.0f, -1.0f));
        DrawCube(glm::vec3(-1.0f, 0.0f, -1.0f));

        DrawCube(glm::vec3(2.0f, 0.0f, 2.0f));
        DrawCube(glm::vec3(2.0f, 0.0f, -2.0f));
        DrawCube(glm::vec3(-2.0f, 0.0f, 2.0f));
        DrawCube(glm::vec3(-2.0f, 0.0f, -2.0f));

        DrawCube(glm::vec3(2.0f, 0.0f, 1.0f));
        DrawCube(glm::vec3(2.0f, 0.0f, 0.0f));
        DrawCube(glm::vec3(2.0f, 0.0f, -1.0f));
        DrawCube(glm::vec3(-2.0f, 0.0f, 1.0f));
        DrawCube(glm::vec3(-2.0f, 0.0f, 0.0f));
        DrawCube(glm::vec3(-2.0f, 0.0f, -1.0f));

        DrawCube(glm::vec3(1.0f, 0.0f, 2.0f));
        DrawCube(glm::vec3(0.0f, 0.0f, 2.0f));
        DrawCube(glm::vec3(-1.0f, 0.0f, 2.0f));
        DrawCube(glm::vec3(1.0f, 0.0f, -2.0f));
        DrawCube(glm::vec3(0.0f, 0.0f, -2.0f));
        DrawCube(glm::vec3(-1.0f, 0.0f, -2.0f));
        //DrawCube(glm::vec3(0.0f,0.0f,0.0f));
        //test data generate
        //ChunkModel test;
        // BlockKey temp={rand()%2,1};
        // test.blockDataArr[0]=temp;
        // for (int i=0;i<chunkSize;i++)
        // {
        //     BlockKey temp={rand()%2,1};
        //     test.blockDataArr[i]=temp;
        // }
        //generate end
        // DrawChunk(test,glm::vec3(0.5,0.5,0));
    }

    //load texture
    unsigned int MapDrawer::LoadTexture(string path)
    {
        //load texture
        unsigned int texture;
        glGenTextures(1, &texture);
        int width, height, nrComponents;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format = 3;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(data);
        return texture;
    }

    //compile shader program
    void MapDrawer::AddShader(GLuint ShaderProgram, const char *ShaderText, GLenum ShaderType)
    {
        GLuint Shader = glCreateShader(ShaderType);
        if (Shader == 0)
        {
            fprintf(stderr, "Error creating shader type %d\n", ShaderType);
            exit(1);
        }
        glShaderSource(Shader, 1, &ShaderText, NULL);
        glCompileShader(Shader);
        GLint success;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(Shader, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
            exit(1);
        }

        glAttachShader(ShaderProgram, Shader);
    }

    //link shader programs
    void MapDrawer::CompileShaders()
    {
        string vShader, fShader;
        if (!ReadFile(vsPath, vShader))
        {
            exit(1);
        };
        if (!ReadFile(fsPath, fShader))
        {
            exit(1);
        };

        AddShader(shaderProgram, vShader.c_str(), GL_VERTEX_SHADER);
        AddShader(shaderProgram, fShader.c_str(), GL_FRAGMENT_SHADER);
        GLint Success = 0;
        GLchar ErrorLog[1024] = {0};
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
        if (Success == 0)
        {
            glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
            exit(1);
        }

        glValidateProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
        if (!Success)
        {
            glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
            exit(1);
        }
        glUseProgram(shaderProgram);
    }

    //read shader file
    bool MapDrawer::ReadFile(const char *pFileName, string &outFile)
    {
        ifstream f(pFileName);
        bool ret = false;
        if (f.is_open())
        {
            string line;
            while (getline(f, line))
            {
                outFile.append(line);
                outFile.append("\n");
            }
            f.close();
            ret = true;
        }
        else
        {
            cout << "cna't read file:" + *pFileName << endl;
        }
        return ret;
    }

    void MapDrawer::DrawCube(glm::vec3 offset)
    {
        for (int i = 0; i < 6; i++)
        {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glUniform3fv(glGetUniformLocation(shaderProgram, "offset"), 1, glm::value_ptr(offset));
            glDrawArrays(GL_TRIANGLES, i * 6, 6);
        }
    }

    void MapDrawer::DrawChunk(ChunkModel data, glm::vec3 pos)
    {
        glm::vec3 zero = pos - glm::vec3(CHUNK_LNEGTH / 2, CHUNK_LNEGTH / 2, CHUNK_LNEGTH / 2);
        for (int x = 0; x < CHUNK_LNEGTH; x++)
        {
            for (int z = 0; z < CHUNK_LNEGTH; z++)
            {
                for (int y = 0; y < CHUNK_LNEGTH; y++)
                {
                    glm::vec3 position = zero + glm::vec3(x + 0.5, y + 0.5, z + 0.5);
                    DrawCube(position);
                }
            }
        }
    }

    void MapDrawer::UpdateView(float xoffset, float yoffset)
    {
        Camera::GetInstance().ChangeView(shaderProgram, xoffset, yoffset);
    }

} // namespace DrawSys