#include <Toolbelt.h>

Toolbelt::Toolbelt() : 
	m_currentTool(nullptr)
{
	m_tools.reserve(4);
}

Toolbelt::~Toolbelt()
{
	for (auto tool : m_tools)
		delete tool;
}

void Toolbelt::use()
{
	m_currentTool->use();
}

void Toolbelt::addTool(Tool* t_tool)
{
	m_tools.push_back(t_tool);
	if (!m_currentTool) {
		m_currentTool = t_tool;
	}
}

Tool* const Toolbelt::getCurrentTool()
{
	return m_currentTool;
}
