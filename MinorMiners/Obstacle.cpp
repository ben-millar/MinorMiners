#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f t_position, int t_radius):m_position(t_position), m_radius(t_radius)
{
	m_radiusBigger = m_radius + 10;
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Blue);
	m_body.setPosition(m_position);
}

void Obstacle::collisionStart()
{
	m_body.setFillColor(sf::Color::Red);
	m_body.setRadius(m_radiusBigger);
	m_body.setOrigin(m_radiusBigger, m_radiusBigger);
}

void Obstacle::collisionEnd()
{
	m_body.setFillColor(sf::Color::Blue);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
}
