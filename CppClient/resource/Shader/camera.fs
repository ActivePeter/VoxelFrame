// #version 330 core
// out vec4 FragColor;
// void main()
// {
// 	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
// }

#version 330 core
out vec4 FragColor;

// in vec2 TexCoord;
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec2 TexCoord;
// texture binded
uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
	FragColor = texture(texture1, TexCoord);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	// FragColor = vertexColor;
	// FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

// #version 330 core
// layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0

// out vec4 vertexColor; // 为片段着色器指定一个颜色输出

// void main()
// {
//     gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
//     vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色
// }