#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "AnimatedSprite.h"
#include "TextureHandler.h"

enum class ToolType : uint8_t
{
	NONE,
	TORCH
};

class Tool {
public: 
	Tool() = default;
	Tool(ToolType t_type) : m_type(t_type) { m_textureHandler = TextureHandler::getInstance(); }

	virtual ToolType getType() { return m_type; }
	virtual void use() = 0;

	virtual void drop() = 0;
	virtual void update(sf::Time t_dt, sf::Vector2f t_parentPos) = 0;

	virtual void setTexture(sf::Texture* t_texture) {
		m_sprite.setTexture(*t_texture);
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

	TextureHandler* m_textureHandler;
};