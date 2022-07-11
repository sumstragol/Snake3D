#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glm/glm.hpp"
#include "../shader.hpp"



class Cube
{
public:
	Cube();
	void draw(const glm::mat4 &model) const;
	static float get_side_length();
private:
	void init_buffers();
protected:
	glm::vec3 position;
	static glm::vec3 color;
	static glm::vec3 bcolor;
private:
	unsigned int VBO;
	unsigned int VAO;
	Shader program;

	static glm::mat4 projection;
	static glm::mat4 view;
	
	static float side_length;
};