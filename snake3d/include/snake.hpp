#pragma once
#include "cube.hpp"
#include <vector>
#include <memory>

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Body_part
{
	Cube part;
	// translation of the cube in the world coordiantes
	glm::vec3 translation = glm::vec3(0.0f, -0.18f, 0.0f);
};

class Snake
{
public:
	Snake();
	void change_direction(const Direction d);
	// also apppends a new body part
	void move(const float delta_time);
	void draw() const;
	void grow();
	bool check_for_head_collision(const glm::vec3 &other) const;
	bool is_alive() const;
private:
	bool check_for_collisions();
private:
	static int frame_counter;
	// variable to translate head based on the current direction of the 
	// movement
	// vec2 since changing only x and z axis
	glm::vec2 head_translation;
	// if snake collidated - it is no longer alive
	bool _alive;
	// sets to true after eating food 
	bool _grow;
	std::vector<Body_part> body;
};