#pragma once

#include <vector>

#include "Tool.h"
#include "Torch.h"

class Toolbelt {
public:
	Toolbelt();
	~Toolbelt();

	void use();

	void update(sf::Vector2f t_pos);

	void addTool(Tool* m_tool);

	Tool* const getCurrentTool();

	Tool* dropCurrentTool();

	Torch* getTorch() { return m_torch; }

	std::vector<Tool*>& const getTools() { return m_tools; }
private: 
	std::vector<Tool*> m_tools;

	Tool* m_currentTool;

	Torch* m_torch;
};