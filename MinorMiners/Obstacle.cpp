#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f t_position) 
	: m_position(t_position)
{
	m_body.setSize({ 67.5f, 67.5f });
	m_body.setOrigin(33.75f, 33.75f);
	m_body.setFillColor(sf::Color::Blue);
	m_body.setPosition(m_position);
}

void Obstacle::collisionStart()
{
	m_body.setFillColor(sf::Color::Red);
}

void Obstacle::collisionEnd()
{
	m_body.setFillColor(sf::Color::Blue);
}
