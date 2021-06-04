// #include "glad/glad.h"
#include "Mesh.h"
#include "GLFW/glfw3.h"

void Mesh::draw()
{
}

Mesh &Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO); //  顶点数组对象
    glGenBuffers(1, &VBO);      //顶点缓冲对象
    glGenBuffers(1, &EBO);      //顶点索引

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    return *this;
}

Mesh &Mesh::clearVertices()
{
    this->vertices.clear();
    return *this;
}

Mesh &Mesh::pushVertex(Vertex vertex)
{
    this->vertices.push_back(vertex);
    return *this;
}

Mesh &Mesh::clearIndices()
{
    this->indices.clear();
    return *this;
}

Mesh &Mesh::pushIndex(unsigned int index)
{
    this->indices.push_back(index);
    return *this;
}

Mesh::Mesh()
{
}
