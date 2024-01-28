#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f t_position) 
	: m_position(t_position)
{
	m_textures[0] = TextureHandler::getInstance()->getTexture("box");
	m_textures[1] = TextureHandler::getInstance()->getTexture("rock1");
	m_textures[2] = TextureHandler::getInstance()->getTexture("rock2");

	m_sprite.setTexture(*(m_textures[rand() % 3]));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f, m_sprite.getTextureRect().height / 2.f);
	m_sprite.setScale(0.22f, 0.22f);
	m_sprite.setPosition(t_position);

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
