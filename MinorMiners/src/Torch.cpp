#include "Torch.h"
#include <iostream>

Torch::Torch() : 
	Tool(ToolType::TORCH)
{
	m_light.setRange(150);
	m_light.setPosition(450, 200);
}

void Torch::use()
{
}

void Torch::drop()
{
}

void Torch::update(sf::Vector2f t_parentPos)
{
	m_light.setPosition(t_parentPos);
}

Torch::operator sf::Drawable const& ()
{
	return m_light;
}
