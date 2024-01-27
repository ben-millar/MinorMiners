#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

enum class ToolType : uint8_t
{
	NONE,
	TORCH
};

class Tool {
public: 
	Tool() = default;
	Tool(ToolType t_type) : m_type(t_type) {}

	virtual ToolType getType() { return m_type; }
	virtual void use() = 0;

	virtual void drop() = 0;
	virtual void update(sf::Vector2f t_parentPos) = 0;

	virtual operator sf::Drawable const& () = 0;
protected:
	ToolType m_type{ ToolType::NONE };
};