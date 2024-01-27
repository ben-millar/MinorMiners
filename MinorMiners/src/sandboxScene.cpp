#include "sandboxScene.h"

sandboxScene::sandboxScene() : 
	m_fog(candle::LightingArea::Mode::FOG, { 0.0f, 0.0f } , RESOLUTION)
{
	m_torch = new Torch();
	std::cout << "Created Sandbox scene\n";
	m_playerBelt.addTool(m_torch);

	m_edges.emplace_back(sf::Vector2f{SCENE_CENTRE.x,0}, sf::Vector2f{SCENE_CENTRE.x,RESOLUTION.y});

	m_lightSources.push_back(&m_torch->getLight());
	m_lightSources.push_back(&m_player.getLight());

	m_fog.setAreaColor(sf::Color::Black);
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
	for (auto light : m_lightSources)
		light->castLight(m_edges.begin(), m_edges.end());

	m_player.move(t_dT);
}

void sandboxScene::render()
{
	m_fog.clear();
	for (auto light : m_lightSources)
		m_fog.draw(*light);
	m_fog.display();


	m_window->clear(sf::Color(125,125,125));

	m_window->draw(m_player);

	m_window->draw(m_fog);
	
	m_window->display();
}
