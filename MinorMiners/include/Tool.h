#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Tool {
public: 

	virtual void use() = 0;

	virtual void drop() = 0;

	virtual operator sf::Drawable const& () = 0;
private:
};