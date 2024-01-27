#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Obstacle
{
public:
	Obstacle(sf::Vector2f t_position = sf::Vector2f(500.f, 500.f));
	sf::RectangleShape getBody() { return m_body; }
	void collisionStart();
	void collisionEnd();

private:
	sf::RectangleShape m_body;
	sf::Vector2f m_position;
	int m_radius;
};

#endif
