#include "sandboxScene.h"

sandboxScene::sandboxScene() : 
	m_fog(candle::LightingArea::Mode::FOG, { 0.0f, 0.0f } , RESOLUTION)
{
	m_torch = new Torch();
	std::cout << "Created Sandbox scene\n";
	m_playerBelt.addTool(m_torch);

	m_tex.loadFromFile("img.png");

	m_sprite.setTexture(m_tex);
	m_sprite.setPosition({ 150,275 });

	m_rect.setPosition({ 100,50 });
	m_rect.setSize({ 50,100 });
	m_rect.setFillColor(sf::Color::Red);

	m_hiddenRect.setPosition({ 280,280 });
	m_hiddenRect.setSize({ 50,50 });
	m_hiddenRect.setFillColor(sf::Color::Red);

	m_edges.emplace_back(sf::Vector2f{275,200}, sf::Vector2f{250,275});

	m_torch->getLight().castLight(m_edges.begin(), m_edges.end());

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

}

void sandboxScene::render()
{
	m_fog.clear();
	m_fog.draw(m_torch->getLight());
	m_fog.display();


	m_window->clear(sf::Color(125,125,125));

	m_window->draw(m_sprite);
	m_window->draw(m_rect);
	m_window->draw(m_hiddenRect);
	m_window->draw(m_fog);
	
	m_window->display();
}
