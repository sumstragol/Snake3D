#version 330 core

out vec4 FragColor;

in vec4 a_color;

void main()
{
	FragColor = a_color;
}