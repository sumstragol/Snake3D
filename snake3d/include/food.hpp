#include "cube.hpp"

class Food : public Cube
{
public:
	Food();
	void spawn();
	void draw() const;
	glm::vec3 get_position() const;
private:
	static glm::vec3 rand();
};