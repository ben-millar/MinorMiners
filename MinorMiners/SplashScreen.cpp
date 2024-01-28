#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	m_textures = TextureHandler::getInstance();

	m_text.setFont(*m_textures->getFont("Font"));

	std::string text = "VOTE BEST GAME - MINOR MINERS - VOTE BEST GAME\n In this game, you assume the role of an occupational health and safety inspector task with assessing a lithium mine staffed by child laborers, ensuring that their fire alarms comply with safety standards.\n However, things change drastically when a gas leak induces hallucinations, leading you to believe you're trapped in a cave overrun with goblins.\n (Wait... wasn't there just a bunch of kids here?)\n Armed with a clipboard, an array of talking tools(talking.. ? -), and a can - do attitude, your objective is to battle through swarms of goblins to reach the surface.\n (Seriously though, what happened to the ki - )\n You're a man on a mission, and you won't let any goblin stand in your way.\n";

	m_text.setString(text);;
}

void SplashScreen::processEvents()
{
	sf::Event e; 
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

		if (e.type == sf::Event::KeyPressed)
		{
			SceneManager* m = SceneManager::getInstance();
			m->setScene(SceneType::GAMEPLAY);
			break;
		}
	}
	
}

void SplashScreen::update(sf::Time t_dT)
{
}

void SplashScreen::render()
{
	m_window->clear();

	m_window->draw(m_text);

	m_window->display();
}
