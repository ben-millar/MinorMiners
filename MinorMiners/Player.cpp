#include "Player.h"

Player::Player(int t_radius, sf::Vector2f t_position): m_radius(t_radius), m_position(t_position)
{
	m_speed = 0.5f;
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setPosition(m_position);

	m_bloom.setRange(50.0f);
	m_bloom.setPosition({ (float)m_radius, (float)m_radius });
}

void Player::setDirection(sf::Vector2f t_direction)
{
	m_direction = t_direction;
}

bool Player::collides(Obstacle& t_obstacle)
{
	if (m_body.getGlobalBounds().intersects(t_obstacle.getBody().getGlobalBounds()))
	{
		t_obstacle.collisionStart();
		return true;
	}
	else
	{
		t_obstacle.collisionEnd();
		return false;
	}
}

void Player::normaliseMovementVector()
{
	float magnitude = std::sqrt(
		m_direction.x * m_direction.x +
		m_direction.y * m_direction.y
	);

	if (magnitude == 0.0f)
	{
		m_direction = sf::Vector2f(0.0f, 0.0f);
		return;
	}

	m_direction = sf::Vector2f(
		m_direction.x / magnitude,
		m_direction.y / magnitude
	);
}

void Player::move(sf::Time t_dT)
{
	normaliseMovementVector();

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
	m_bloom.setPosition(m_position);
}

void Player::update(sf::Time t_dT)
{
	m_tools.update(m_position);
	move(t_dT);
}

void Player::setDirectionX(float t_x)
{
	m_direction.x = t_x;
}

void Player::setDirectionY(float t_y)
{
	m_direction.y = t_y;
}
