#version 330 core

in vec4 acolor;
out vec4 FragColor;

uniform vec3 color;

void main()
{
	FragColor = acolor;
}