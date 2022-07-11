#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glm/glm.hpp"
#include "../shader.hpp"

class Floor
{
public:
	Floor(const glm::mat4& floor_view);
	void draw() const;
private:
	unsigned int VBO;
	unsigned int VAO;
	glm::mat4 floor_view;
	Shader program;
};