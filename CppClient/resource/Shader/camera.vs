#version 330 core
layout (location = 0) in vec3 aPos;
//材质uv坐标
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 vertexColor; 

// uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0f);
	// gl_Position = vec4(aPos, 1.0f);

	// TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
	TexCoord =aTexCoord; 
}

// #version 330 core
// layout (location = 0) in vec3 aPos;
// void main()
// {
// 	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
// }