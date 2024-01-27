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

void Toolbelt::update(sf::Vector2f t_pos)
{
	for (auto tool : m_tools) {
		tool->update(t_pos);
	}
}

void Toolbelt::addTool(Tool* t_tool)
{
	m_tools.push_back(t_tool);
	if (!m_currentTool) {
		m_currentTool = t_tool;
	}
	if (t_tool->getType() == ToolType::TORCH) {
		m_torch = dynamic_cast<Torch*>(t_tool);
	}
}

Tool* const Toolbelt::getCurrentTool()
{
	return m_currentTool;
}

Tool* Toolbelt::dropCurrentTool()
{
	if (m_tools.size() == 0)
		return nullptr;

	Tool* currentTool = nullptr;
	for (auto it = m_tools.begin(); it != m_tools.end(); ++it)
	{
		if (*it == m_currentTool)
		{
			if (m_currentTool == m_torch)
				m_torch = nullptr;	
			currentTool = *it;
			m_tools.erase(it);
			break;
		}
	}
	return currentTool;
}
