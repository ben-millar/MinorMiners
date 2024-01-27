#include "Enemy.h"

Enemy::Enemy(sf::Vector2f t_position, int t_radius):m_position(t_position),m_radius(t_radius)
{
	m_speed = 0.5f;
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Green);
	m_body.setPosition(m_position);
	pickTargetPosition();
}
void Enemy::normaliseMovementVector()
{
	float magnitude = calculateMagnitude();

	if (magnitude == 0.0f)
	{
		m_target = sf::Vector2f(0.0f, 0.0f);
		return;
	}

	m_direction = sf::Vector2f(
		(m_target.x-m_position.x) / magnitude,
		(m_target.y-m_position.y) / magnitude
	);
}

float Enemy::calculateMagnitude()
{
	return std::sqrt(
		(m_position.x - m_target.x)*(m_position.x - m_target.x) +
		(m_position.y - m_target.y)* (m_position.y - m_target.y)
	);
}

void Enemy::move(sf::Time t_dT)
{
	if (calculateMagnitude()>m_radius)
	{
		m_position.x += m_direction.x * m_speed * t_dT.asMilliseconds();
		m_position.y += m_direction.y * m_speed * t_dT.asMilliseconds();
		m_body.setPosition(m_position);
	}
	else
	{
		pickTargetPosition();
		//m_direction=sf::Vector2f(0.f,0.f);
	}
}

void Enemy::pickTargetPosition()
{
	int rNumX = rand() % static_cast<int>(RESOLUTION.x);
	int rNumY = rand() % static_cast<int>(RESOLUTION.y);
	m_target = sf::Vector2f(rNumX, rNumY);
	m_bodyTarget.setRadius(m_radius);
	m_bodyTarget.setOrigin(m_radius, m_radius);
	m_bodyTarget.setFillColor(sf::Color::Green);
	m_bodyTarget.setPosition(m_target);
	normaliseMovementVector();
}
