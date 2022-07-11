#include "../include/snake.hpp"	
#include "../glm/gtc/matrix_transform.hpp"

int Snake::frame_counter = 0;

Snake::Snake()
	:_alive(true), _grow(false)
{
	// init first body part
	Body_part head;
	head.part = Cube();
	
	body.push_back(head);

	head_translation = glm::vec2(0.0f, Cube::get_side_length() * 2.0f);
}

void Snake::change_direction(const Direction d)
{
	const float step_length = Cube::get_side_length() * 2.0f;

	switch (d)
	{
	case Direction::LEFT:
	{
		head_translation = glm::vec2(-step_length, 0.0f);
		break;
	}
	case Direction::RIGHT:
	{
		head_translation = glm::vec2(step_length, 0.0f);
		break;
	}
	case Direction::UP:
	{
		head_translation = glm::vec2(0.0f, -step_length);
		break;
	}
	case Direction::DOWN:
	{
		head_translation = glm::vec2(0.0f, step_length);
		break;
	}
	}
	
}

void Snake::move(const float delta_time)
{
	if (frame_counter != 50)
	{
		frame_counter++;
		return;
	}

	frame_counter = 0;

	// move head
	glm::vec3 tcpy = body[0].translation;
	body[0].translation += glm::vec3(head_translation.x, 0.0f, head_translation.y);

	// swap loop
	// move the rest of the body parts
	// - copy translation of the previous body part
	for (int i = 1; i < body.size(); ++i)
	{
		std::swap(tcpy, body[i].translation);
	}

	if (_grow)
	{
		Body_part new_part;
		new_part.part = Cube();
		// translation of the last cube after finishing the swap loop
		new_part.translation = tcpy;
		body.push_back(new_part);
		_grow = false;
	}

	check_for_collisions();
}

void Snake::draw() const
{
	for (int i = 0; i < body.size(); ++i)
	{
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, body.at(i).translation);
 		body.at(i).part.draw(model);
	}
}

void Snake::grow()
{
	_grow = true;
}

bool Snake::check_for_head_collision(const glm::vec3& other) const
{
	return body[0].translation == other;
}

bool Snake::is_alive() const
{
	return _alive;
}

bool Snake::check_for_collisions()
{
	for (int i = 0; i < body.size(); ++i)
	{
		for (int j = 0; j < body.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}

			if (body[i].translation == body[j].translation)
			{
				_alive = false;
				return true;
			}
		}
	}

	return false;
}
