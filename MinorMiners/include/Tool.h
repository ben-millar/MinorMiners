#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "AnimatedSprite.h"

enum class ToolType : uint8_t
{
	NONE,
	TORCH
};

class Tool {
public: 
	Tool() = default;
	Tool(ToolType t_type) : m_type(t_type), m_texture(nullptr) {}

	virtual ToolType getType() { return m_type; }
	virtual void use() = 0;

	virtual void drop() = 0;
	virtual void update(sf::Vector2f t_parentPos) = 0;

	virtual void setTexture(sf::Texture* t_texture) {
		m_texture = t_texture;
		m_sprite.setTexture(*m_texture);
	}

	virtual sf::AnimatedSprite& getSprite() {
		return m_sprite;
	}

	virtual operator sf::Drawable const& () {
		return m_sprite;
	}
protected:
	ToolType m_type{ ToolType::NONE };
	sf::AnimatedSprite m_sprite;
	sf::Texture* m_texture; 
};