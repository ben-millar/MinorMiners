#pragma once

#include "Tool.h"
#include <SFML/Graphics.hpp>

#include <Candle/RadialLight.hpp>

class Torch : public Tool
{
public: 
	Torch();
	Torch(sf::Vector2f t_pos);
	~Torch() = default;

	virtual void use()override;

	virtual void drop()override;

	virtual void update(sf::Time t_dt, sf::Vector2f t_parentPos)override;

	virtual candle::RadialLight& getLight() { return m_light; }

	operator candle::LightSource const& () {
		return m_light;
	}

private:
	candle::RadialLight m_light;
};