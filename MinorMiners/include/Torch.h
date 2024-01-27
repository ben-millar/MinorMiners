#pragma once

#include "Tool.h"
#include <SFML/Graphics.hpp>

#include <Candle/RadialLight.hpp>

class Torch : public Tool
{
public: 
	Torch();
	~Torch() = default;

	virtual void use()override;

	virtual void drop()override;

	virtual void update(sf::Vector2f t_parentPos)override;

	virtual candle::RadialLight& getLight() { return m_light; }

	operator candle::LightSource const& () {
		return m_light;
	}

private:
	sf::Sprite m_torchSprite;
	sf::Texture m_torchTexture;

	candle::RadialLight m_light;
};