#pragma once

#include <SFML/Graphics.hpp>

struct DoorState {
	DoorState(
		bool t_north = true,
		bool t_south = true,
		bool t_east = true,
		bool t_west = true) :
		north{ t_north },
		south{ t_south },
		east{ t_east },
		west{ t_west } {}

	bool north, south, east, west;
};

class Door
{
public:
	Door(sf::Vector2f t_position, sf::Texture* t_texture) :
		m_position{t_position} 
	{
		m_collider.setFillColor(sf::Color::Red);
		m_collider.setSize({ 200.f, 200.f });
		m_collider.setOrigin(100.f, 100.f);

		m_collider.setPosition(m_position);

		m_texture = *t_texture;
		m_sprite.setTexture(*t_texture);
		m_sprite.setScale(0.3f, 0.3f);
		m_sprite.setPosition(t_position);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	}

	~Door() = default;

	void setTexture(sf::Texture t_texture) {
		m_texture = t_texture;
		m_sprite.setTexture(t_texture);
	}

	sf::Sprite getSprite() { return m_sprite; }
	sf::FloatRect getCollider() { return m_collider.getGlobalBounds(); }
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_collider;
	sf::Vector2f m_position;
};