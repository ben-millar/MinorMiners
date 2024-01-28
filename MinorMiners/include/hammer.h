#pragma once

#include "Tool.h"


class Hammer : public Tool {
public: 
	Hammer() {};
	~Hammer() = default;

	virtual void use() override {};

	virtual void drop()override {};

	virtual void update(sf::Time t_dt, sf::Vector2f t_parentPos)override {};

private:
};