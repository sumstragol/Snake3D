#include "../include/floor.hpp"


Floor::Floor(const glm::mat4& floor_view)
	:floor_view(floor_view)
{
	program = Shader("shaders/floor.vs", "shaders/floor.fs");
	program.use();
	program.setMat4("floor_view", floor_view);

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	const float tile_width = 0.2f;
	const float vertices[] = {
		-tile_width, -tile_width, -tile_width,  color.x, color.y, color.z,
		 tile_width, -tile_width, -tile_width,  color.x, color.y, color.z,
		-tile_width, -tile_width,  tile_width,  color.x, color.y, color.z,
		 tile_width, -tile_width,  tile_width,  color.x, color.y, color.z,
		 tile_width, -tile_width, -tile_width,  color.x, color.y, color.z,
		-tile_width, -tile_width,  tile_width,  color.x, color.y, color.z,
	};

	// gen
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind
	glBindVertexArray(VAO);
	// vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// layouts
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Floor::draw() const
{
	program.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
