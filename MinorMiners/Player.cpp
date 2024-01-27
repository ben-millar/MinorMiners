#include "Player.h"

Player::Player(int t_radius, sf::Vector2f t_position): m_radius(t_radius), m_position(t_position)
{
	m_speed = 0.5f;
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setPosition(m_position);
}

void Player::setDirection(sf::Vector2f t_direction)
{
	m_direction = t_direction;
}

void Player::move(sf::Time t_dT)
{
	m_position.x += m_direction.x * m_speed* t_dT.asMilliseconds();
	m_position.y += m_direction.y * m_speed* t_dT.asMilliseconds();
	if (m_position.x-m_radius < 0)
	{
		m_position.x = 0+m_radius;
	}
	else if (m_position.x + m_radius > RESOLUTION.x)
	{
		m_position.x = RESOLUTION.x -m_radius;
	}

	if (m_position.y - m_radius < 0)
	{
		m_position.y = 0+m_radius;
	}
	else if (m_position.y + m_radius > RESOLUTION.y)
	{
		m_position.y = RESOLUTION.y - m_radius;
	}
	m_body.setPosition(m_position);
}

void Player::setDirectionX(float t_x)
{
	m_direction.x = t_x;
}

void Player::setDirectionY(float t_y)
{
	m_direction.y = t_y;
}
