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
	Door(sf::Vector2f t_position) :
		m_position{t_position} 
	{
		m_collider.setFillColor(sf::Color::Red);
		m_collider.setSize({ 200.f, 200.f });
		m_collider.setOrigin(100.f, 100.f);

		m_collider.setPosition(m_position);
	}

	~Door() = default;

	sf::RectangleShape getSprite() { return m_collider; }
	sf::FloatRect getCollider() { return m_collider.getGlobalBounds(); }
private:
	sf::RectangleShape m_collider;
	sf::Vector2f m_position;
};