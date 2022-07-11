#include "../include/food.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <time.h>
#include <stdlib.h>


Food::Food()
{
	Cube::color = glm::vec3(0.1f, 0.8f, 0.14f);
	Cube::bcolor = glm::vec3(0.1f, 0.1f, 0.14f);
	position = rand();

	srand(time(NULL));
}

void Food::spawn()
{
	position = rand();
}

void Food::draw() const
{
	auto model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, position);
	Cube::draw(model);
}


glm::vec3 Food::get_position() const
{
	return position;
}

glm::vec3 Food::rand()
{
	// 5 * 2current_side_length == 2.0f
	// which still fits on the screen
	int x_scalar = std::rand() % 6;
	int y_scalar = std::rand() % 6;
	int x_neg_mult = (static_cast<int>(std::rand() % 2) == 0) ? 1 : -1;
	int y_neg_mult = (static_cast<int>(std::rand() % 2) == 0) ? 1 : -1;
	return glm::vec3(
		x_neg_mult * x_scalar * 2.0f * Cube::get_side_length(),
		-0.18f,
		y_neg_mult * y_scalar * 2.0f * Cube::get_side_length()
	);
}
