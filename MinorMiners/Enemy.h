#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Enemy
{
public:
	Enemy(sf::Vector2f t_position=sf::Vector2f(300.f,400.f),int t_radius=20);
	sf::CircleShape getBody() { return m_body; }
	sf::CircleShape getBodyTarget() { return m_bodyTarget; }
	void move(sf::Time t_dT);
	void pickTargetPosition();
	void normaliseMovementVector();
	float calculateMagnitude();
private:
	sf::CircleShape m_body;
	sf::Vector2f m_position;
	sf::Vector2f m_target;
	int m_radius;
	float m_speed;
	sf::Vector2f m_direction;
	sf::CircleShape m_bodyTarget;
};

#endif
