#pragma once

#include "Tool.h"


class Hammer : public Tool {
public: 
	Hammer();
	~Hammer() = default;

	virtual void use() override; 

	virtual void drop()override;

	virtual void update(sf::Vector2f t_parentPos)override;
	operator sf::Drawable const& ()override;

private:
};