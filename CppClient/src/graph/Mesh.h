#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include <learnopengl/shader.h>
#include "base.h"

#include <string>
#include <vector>
using namespace std;

struct Vertex
{
    // position
    glm::vec3 Position;
    // // normal
    // glm::vec3 Normal;
    // // texCoords
    // glm::vec2 TexCoords;
    // // tangent
    // glm::vec3 Tangent;
    // // bitangent
    // glm::vec3 Bitangent;
    void setPostion(float x, float y, float z)
    {
        Position = glm::vec3(x, y, z);
    }
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh()
    {
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

    // render the mesh
    void draw()
    {
        std::cout << "chunk on draw" << std::endl;
        // Shader &shader;
        // // bind appropriate textures
        // unsigned int diffuseNr = 1;
        // unsigned int specularNr = 1;
        // unsigned int normalNr = 1;
        // unsigned int heightNr = 1;
        // for (unsigned int i = 0; i < textures.size(); i++)
        // {
        //     glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //     // retrieve texture number (the N in diffuse_textureN)
        //     string number;
        //     string name = textures[i].type;
        //     if (name == "texture_diffuse")
        //         number = std::to_string(diffuseNr++);
        //     else if (name == "texture_specular")
        //         number = std::to_string(specularNr++); // transfer unsigned int to stream
        //     else if (name == "texture_normal")
        //         number = std::to_string(normalNr++); // transfer unsigned int to stream
        //     else if (name == "texture_height")
        //         number = std::to_string(heightNr++); // transfer unsigned int to stream

        //     // now set the sampler to the correct texture unit
        //     glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        //     // and finally bind the texture
        //     glBindTexture(GL_TEXTURE_2D, textures[i].id);
        // }

        // // draw mesh
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // // always good practice to set everything back to defaults once configured.
        // glActiveTexture(GL_TEXTURE0);
    }
    void setupMesh()
    {
        if (!inited)
        {
            setupResourceTest();
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
        }
        // create buffers/arrays

        glBindVertexArray(VAO);
        // // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // // A great thing about structs is that their memory layout is sequential for all its items.
        // // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // // set the vertex attribute pointers
        // // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // // vertex normals
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
        // // vertex texture coords
        // glEnableVertexAttribArray(2);
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
        // // vertex tangent
        // glEnableVertexAttribArray(3);
        // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
        // // vertex bitangent
        // glEnableVertexAttribArray(4);
        // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }

private:
    // render data
    unsigned int VBO, EBO;
    bool inited = false;
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    unsigned int shaderProgram;
    // initializes all the buffer objects/arrays
    void setupResourceTest()
    {
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
};