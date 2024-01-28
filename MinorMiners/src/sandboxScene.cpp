#include "sandboxScene.h"

sandboxScene::sandboxScene() : 
	m_fog(candle::LightingArea::Mode::FOG, { 0.0f, 0.0f } , RESOLUTION)
{
	m_edges.emplace_back(sf::Vector2f{SCENE_CENTRE.x,0}, sf::Vector2f{SCENE_CENTRE.x,RESOLUTION.y});

	m_lightSources.push_back(&m_player.getLight());

	m_fog.setAreaColor(sf::Color::Black);

	Torch* t = new Torch();
	t->getLight().setPosition({ 300,300 });

	m_environmentTools.push_back(t);
}

void sandboxScene::processEvents()
{
	sf::Event e;

	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

		if (e.type == sf::Event::KeyPressed)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_window->close();
				break;
			case sf::Keyboard::Left:
				m_player.setDirectionX(-1.0f);
				break;
			case sf::Keyboard::Right:
				m_player.setDirectionX(1.0f);
				break;
			case sf::Keyboard::Up:
				m_player.setDirectionY(-1.0f);
				break;
			case sf::Keyboard::Down:
				m_player.setDirectionY(1.0f);
				break;
			case sf::Keyboard::E:
				if (auto iter = m_environmentTools.begin(); iter != m_environmentTools.end()) {
					m_player.addTool(*iter);
					m_environmentTools.erase(iter);
				}
				break;
			case sf::Keyboard::Q:
				if (auto tool = m_player.dropTool(); tool != nullptr)
					m_environmentTools.push_back(tool);
				break;
			default:
				break;
			}
		}
		if (e.type == sf::Event::KeyReleased)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Left:
				m_player.setDirectionX(0.0f);
				break;
			case sf::Keyboard::Right:
				m_player.setDirectionX(0.0f);
				break;
			case sf::Keyboard::Up:
				m_player.setDirectionY(0.0f);
				break;
			case sf::Keyboard::Down:
				m_player.setDirectionY(0.0f);
				break;
			default:
				break;
			}
		}

		if (e.type == sf::Event::MouseButtonPressed)
		{
		}

		if (e.type == sf::Event::MouseButtonReleased)
		{
		}
	}
}

void sandboxScene::update(sf::Time t_dT)
{
	updateFog();

	m_player.update(t_dT);
}

void sandboxScene::render()
{
	renderFog();

	m_window->clear(sf::Color(125,125,125));

	m_window->draw(m_player);

	m_window->draw(m_fog);
	
	m_window->display();
}

void sandboxScene::renderFog()
{
	m_fog.clear();
	for (auto light : m_lightSources)
		m_fog.draw(*light);

	for (auto light : m_environmentTools)
		if (light->getType() == ToolType::TORCH)
			m_fog.draw(*dynamic_cast<Torch*>(light));

	if (m_player.getTorch())
		m_fog.draw(*m_player.getTorch());

	m_fog.display();
}

void sandboxScene::updateFog()
{
	for (auto light : m_lightSources)
		light->castLight(m_edges.begin(), m_edges.end());

	for (auto light : m_environmentTools)
		if (light->getType() == ToolType::TORCH)
			dynamic_cast<Torch*>(light)->getLight().castLight(m_edges.begin(), m_edges.end());
	if (m_player.getTorch())
		m_player.getTorch()->getLight().castLight(m_edges.begin(), m_edges.end());
}
