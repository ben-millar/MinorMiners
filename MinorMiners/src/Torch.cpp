#include "Torch.h"
#include <iostream>

Torch::Torch() : 
	Torch({ 450,200 })
{
}

Torch::Torch(sf::Vector2f t_pos) : 
	Tool(ToolType::TORCH)
{

	m_light.setRange(600);
	m_light.setIntensity(0.65f);
	m_light.setPosition(t_pos);

	m_sprite.initTexture(State::Walking_down, m_textureHandler->getTexture("Torch"), 8);
	m_sprite.setFramteDelay(0.25f);
	m_sprite.setState(State::Walking_down);
	m_sprite.setPosition(t_pos);
}

void Torch::use()
{
}

void Torch::drop()
{
}

void Torch::update(sf::Time t_dt, sf::Vector2f t_parentPos)
{
	m_light.setPosition(t_parentPos);

	m_sprite.setPosition(t_parentPos);
	m_sprite.update(t_dt);
}