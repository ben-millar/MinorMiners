#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <array>

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "TextureHandler.h"

class Obstacle
{
public:
	Obstacle(sf::Vector2f t_position = sf::Vector2f(0.f, 0.f));
	sf::RectangleShape getBody() { return m_body; }
	sf::Sprite getSprite() { return m_sprite; }
	void collisionStart();
	void collisionEnd();

private:
	std::array<sf::Texture*, 3> m_textures;
	sf::Sprite m_sprite;

	sf::RectangleShape m_body;
	sf::Vector2f m_position;
	int m_radius;
};

#endif
