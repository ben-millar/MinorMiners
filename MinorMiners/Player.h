#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Obstacle.h"
#include "Enemy.h"

#include <Candle/RadialLight.hpp>
#include "Toolbelt.h"
#include "AnimatedSprite.h"

class Player
{
public:
	Player(sf::Vector2f t_position=sf::Vector2f(200.0f,200.0f));

	void move(sf::Time t_dT);
	void update(sf::Time t_dT);
	void setDirectionX(float t_x);
	void setDirectionY(float t_y);
	void setDirection(sf::Vector2f t_position);
	bool collides(Obstacle& t_obstacle);

	void checkCollisions(std::vector<sf::FloatRect> t_colliders);
	void checkInBounds();

	sf::Vector2f getPosition() { return m_position; }
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }
	
	candle::RadialLight& getLight() { return m_bloom; }

	operator sf::Drawable const& () { return m_sprite; }

	void addTool(Tool* t_tool) { m_tools.addTool(t_tool); }

	Tool* dropTool() { return m_tools.dropCurrentTool(); }
	
	Torch* getTorch() { return m_tools.getTorch(); }

private:
	void loadTexture();
	sf::AnimatedSprite m_sprite;
	sf::Texture m_walkingRightTexture;
	sf::Texture m_walkingLeftTexture;
	sf::Texture m_walkingVerticalTexture;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	int m_radius;
	float m_speed;

	candle::RadialLight m_bloom;
	Toolbelt m_tools;

	void normaliseMovementVector();
};




#endif