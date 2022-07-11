#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 acolor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	acolor = vec4(color, 1.0f);
}