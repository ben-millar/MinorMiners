#include "AnimatedSprite.h"

void sf::AnimatedSprite::update(Time t_dt)
{
	m_frameCounter += t_dt.asSeconds();

	if (m_frameCounter > m_frameDelay) {
		IntRect rect = m_size;
		rect.left = rect.width * (++m_current % m_currentTexture.frames);
		setTextureRect(rect);
		m_frameCounter = 0;
	}
}
