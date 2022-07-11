#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 a_color;
uniform mat4 floor_view;

void main()
{
	gl_Position = floor_view * vec4(pos, 1.0f);
	a_color = vec4(color, 1.0f);
}