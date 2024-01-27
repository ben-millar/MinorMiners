#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Obstacle.h"

class Player
{
public:
	Player(int t_radius=15, sf::Vector2f t_position=sf::Vector2f(20.0f,20.0f));

	void move(sf::Time t_dT);
	sf::CircleShape getBody() { return m_body; }
	void setDirectionX(float t_x);
	void setDirectionY(float t_y);
	void setDirection(sf::Vector2f t_position);
	bool collides(Obstacle& t_obstacle);

private:
	sf::CircleShape m_body;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	int m_radius;
	float m_speed;

	void normaliseMovementVector();
};




#endif