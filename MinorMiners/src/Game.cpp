#include "Game.h"

void Game::run()
{
	m_window = createWindow("Minor Miners");
	m_window->setKeyRepeatEnabled(false);
	m_window->setView({ SCENE_CENTRE, RESOLUTION });

	auto sceneManager = SceneManager::getInstance();
	sceneManager->setWindow(m_window);

	sceneManager->registerScene<GameplayScene>(SceneType::GAMEPLAY);
	sceneManager->registerScene<SplashScreen>(SceneType::SPLASH);
	sceneManager->registerScene<sandboxScene>(SceneType::SANDBOX);
	sceneManager->setScene(SceneType::SPLASH);

	loadTextures();

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.f);

	while (m_window->isOpen()) {
		sf::Time dT = clock.restart();
		lag += dT;

		sceneManager->processEvents();

		while (lag > MS_PER_UPDATE) {
			sceneManager->update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		sceneManager->update(dT);
		sceneManager->render();
	}
}

void Game::loadTextures()
{
}

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		t_title, sf::Style::Titlebar | sf::Style::Close
	);
}
