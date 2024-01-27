#pragma once

#include <vector>

#include "Tool.h"

class Toolbelt {
public:
	Toolbelt();
	~Toolbelt();

	void use();

	void addTool(Tool* m_tool);

	Tool* const getCurrentTool();
private: 
	std::vector<Tool*> m_tools;

	Tool* m_currentTool;
};