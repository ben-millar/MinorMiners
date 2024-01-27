#pragma once

#include "Tool.h"
#include <SFML/Graphics.hpp>

#include <Candle/RadialLight.hpp>

class Torch : public Tool
{
public: 
	Torch();
	~Torch() = default;

	virtual void use();

	virtual void drop();

	virtual void update(sf::Vector2f t_parentPos);

	virtual candle::RadialLight& getLight() { return m_light; }

	operator sf::Drawable const& ();

private:
	sf::Sprite m_torchSprite;
	sf::Texture m_torchTexture;

	candle::RadialLight m_light;
};