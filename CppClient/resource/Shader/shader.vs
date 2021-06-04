#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 texCoord;
//uniform mat4 rotate;
uniform mat4 camera;
uniform mat4 projection;
uniform vec3 offset;
void main()
{
    gl_Position = projection*camera*vec4(aPos+offset, 1.0);
    texCoord=aTexCoord;
}