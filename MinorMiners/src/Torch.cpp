#include "Torch.h"
#include <iostream>

Torch::Torch()
{
	m_light.setRange(350);
	m_light.setPosition(200, 200);
}

void Torch::use()
{
}

void Torch::drop()
{
}

Torch::operator sf::Drawable const& ()
{
	return m_light;
}
