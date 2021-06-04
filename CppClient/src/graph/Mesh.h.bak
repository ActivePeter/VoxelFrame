#pragma once
#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include "string"
#include "vector"

#include "glm/glm.hpp"

#include "./interface/Drawer.h"

using std::string;
using std::vector;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    string type;
};

class Mesh : public Drawer
{
public:
    vector<Texture> textures;
    /*  函数  */
    Mesh();
    // Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // void Draw(Shader shader);

    void draw();
    Mesh &setupMesh();

    //清除顶点数据
    Mesh &clearVertices();
    //加入顶点
    Mesh &pushVertex(Vertex vertex);

    //清除索引
    Mesh &clearIndices();
    //加入索引
    Mesh &pushIndex(unsigned int index);

private:
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
};