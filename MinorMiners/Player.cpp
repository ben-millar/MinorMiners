#include "Player.h"

Player::Player(sf::Vector2f t_position): m_position(t_position)
{
	m_speed = 0.5f;
	m_direction = sf::Vector2f(0.0f, 0.0f);

	loadTexture();

	m_sprite.setFramteDelay(0.25);
	m_sprite.setScale(0.075f, 0.075f);
	m_sprite.initTexture(State::Walking_left, &m_walkingLeftTexture, 4);
	m_sprite.initTexture(State::Walking_right, &m_walkingRightTexture, 4);
	m_sprite.initTexture(State::Walking_down, &m_walkingVerticalTexture, 3);
	m_sprite.initTexture(State::Standing, &m_walkingVerticalTexture, 1);
	m_sprite.setState(State::Standing);

	m_bloom.setRange(250.0f);
	m_bloom.setPosition({ (float)m_sprite.getTextureRect().width, (float)m_sprite.getTextureRect().height});
}

void Player::setDirection(sf::Vector2f t_direction)
{
	m_direction = t_direction;
}

bool Player::collides(Obstacle& t_obstacle)
{
	if (m_sprite.getGlobalBounds().intersects(t_obstacle.getBody().getGlobalBounds()))
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

void Player::loadTexture()
{
	if (!m_walkingRightTexture.loadFromFile("assets/images/moveright.png")) {
		std::cout << "ERROR Loading Walking Right Texture\n";
	}
	if (!m_walkingLeftTexture.loadFromFile("assets/images/moveleft.png")) {
		std::cout << "ERROR Loading Walking Left Texture\n";
	}
	if (!m_walkingVerticalTexture.loadFromFile("assets/images/spritewalk.png")) {
		std::cout << "ERROR Loading Walking Left Texture\n";
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
	if (m_direction.y != 0)
		m_sprite.setState(State::Walking_down);

	if (m_direction.x > 0) 
		m_sprite.setState(State::Walking_right);
	else if (m_direction.x < 0)
		m_sprite.setState(State::Walking_left);

	float magnitude = std::sqrt(
		m_direction.x * m_direction.x +
		m_direction.y * m_direction.y
	);

	if (magnitude == 0)
		m_sprite.setState(State::Standing);

	m_position.x += m_direction.x * m_speed* t_dT.asMilliseconds();
	m_position.y += m_direction.y * m_speed* t_dT.asMilliseconds();
	/*if (m_position.x-m_radius < 0)
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
	}*/
	m_sprite.setPosition(m_position);
	m_bloom.setPosition(m_position);
}

void Player::update(sf::Time t_dT)
{
	m_sprite.update(t_dT);
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
