#include "Player.h"

Player::Player(sf::Vector2f t_position): m_position(t_position)
{
	m_speed = 0.13f;

	m_direction = sf::Vector2f(0.0f, 0.0f);

	loadTexture();

	m_sprite.setFramteDelay(0.25);
	m_sprite.setScale(0.075f, 0.075f);
	m_sprite.setState(State::Standing);

	sf::IntRect texRect = m_sprite.getTextureRect();

	m_sprite.setOrigin({
		(float)texRect.width / 2.f,
		(float)texRect.height / 2.f
		});

	m_collider.setRadius(m_sprite.getGlobalBounds().width / 2.5f);
	m_collider.setOrigin(m_collider.getRadius(), m_collider.getRadius());
	m_collider.setFillColor(sf::Color(255,0,0,128));

	m_bloom.setRange(250.0f);
	m_bloom.setPosition({
		(float)texRect.width / 2.f,
		(float)texRect.height / 2.f
		});
	m_bloom.setIntensity(0.5);
}

void Player::setDirection(sf::Vector2f t_direction)
{
	m_direction = t_direction;
}

bool Player::collides(Obstacle& t_obstacle)
{
	if (m_collider.getGlobalBounds().intersects(t_obstacle.getBody().getGlobalBounds()))
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
	TextureHandler* handler = TextureHandler::getInstance();
	auto walkingLeft = handler->getTexture("PlayerMoveLeft");
	auto walkingRight = handler->getTexture("PlayerMoveRight");
	auto walkingVertical = handler->getTexture("playerMoveVertical");

	m_sprite.initTexture(State::Walking_left, walkingLeft, 4);
	m_sprite.initTexture(State::Walking_right, walkingRight, 4);
	m_sprite.initTexture(State::Walking_down, walkingVertical, 3);
	m_sprite.initTexture(State::Standing, walkingVertical, 1);
}

void Player::checkCollisions(std::vector<sf::FloatRect> t_colliders)
{
	for (auto& rect : t_colliders) {
		if (!m_collider.getGlobalBounds().intersects(rect)) continue;

		auto playerBounds = m_collider.getGlobalBounds();

		// Calculate the overlap on each axis
		float overlapLeft = playerBounds.left + playerBounds.width - rect.left;
		float overlapRight = rect.left + rect.width - playerBounds.left;
		float overlapTop = playerBounds.top + playerBounds.height - rect.top;
		float overlapBottom = rect.top + rect.height - playerBounds.top;

		// Find the smallest overlap. We assume this is the best axis to push apart on.
		bool pushFromLeftOrRight = overlapLeft < overlapRight;
		bool pushFromTopOrBottom = overlapTop < overlapBottom;

		float minOverlapX = pushFromLeftOrRight ? overlapLeft : overlapRight;
		float minOverlapY = pushFromTopOrBottom ? overlapTop : overlapBottom;

		// Resolve collision along the smallest overlap axis
		if (minOverlapX < minOverlapY) {
			if (pushFromLeftOrRight) {
				m_position.x -= minOverlapX;
			}
			else {
				m_position.x += minOverlapX;
			}
		}
		else {
			if (pushFromTopOrBottom) {
				m_position.y -= minOverlapY;
			}
			else {
				m_position.y += minOverlapY;
			}
		}
	}
}

void Player::checkInBounds()
{
	const float TOP_BOUND{ 150 };
	const float BOTTOM_BOUND{ 920 };
	const float LEFT_BOUND{ 130 };
	const float RIGHT_BOUND{ 970 };

	if (m_position.x-m_radius < LEFT_BOUND)
	{
		m_position.x = LEFT_BOUND+m_radius;
	}
	else if (m_position.x + m_radius > RIGHT_BOUND)
	{
		m_position.x = RIGHT_BOUND -m_radius;
	}

	if (m_position.y - m_radius < TOP_BOUND)
	{
		m_position.y = TOP_BOUND+m_radius;
	}
	else if (m_position.y + m_radius > BOTTOM_BOUND)
	{
		m_position.y = BOTTOM_BOUND - m_radius;
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

	m_position.x += m_direction.x * m_speed * ((double)t_dT.asMicroseconds() / 1000.);
	m_position.y += m_direction.y * m_speed * ((double)t_dT.asMicroseconds() / 1000.);

	m_collider.setPosition(m_position + sf::Vector2f(0.f, m_sprite.getGlobalBounds().height / 4.f));
	
	m_sprite.setPosition(m_position);
	// This doesn't work, I blame Aaron
	//sf::Vector2f spriteSize = static_cast<sf::Vector2f>(m_sprite.getTextureRect().getSize()) / 2.0f;
	sf::Vector2f spriteSize = { 
		(float)m_sprite.getTextureRect().width / 2.f,
		(float)m_sprite.getTextureRect().height / 2.f
	};

	spriteSize.x *= m_sprite.getScale().x;
	spriteSize.y *= m_sprite.getScale().y;
	m_bloom.setPosition(m_position + spriteSize);
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
