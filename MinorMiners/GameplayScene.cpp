#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	std::cout << "Creating " << typeid(*this).name() << std::endl;

	m_levelData = LevelLoader::getInstance()->load("assets/level_data/levels.json");

	setLevel(m_currentLevel);

	loadAudio();
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::processEvents()
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
			case sf::Keyboard::Num1:
				setLevel(0);
				break;
			case sf::Keyboard::Num2:
				setLevel(1);
				break;
			case sf::Keyboard::Space:
				playRandomAudio();
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

void GameplayScene::update(sf::Time t_dT)
{
	// Do game update here
	m_player.move(t_dT);
	m_kid.move(t_dT);

	for (auto& obstacle : m_obstacles) {
		m_player.collides(obstacle);
	}

	for (auto& wall : m_walls) {
		m_player.collides(wall);
	}

	checkPlayerPosition();

}

void GameplayScene::render()
{
	m_window->clear(sf::Color::Transparent);

	// Draw your stuff here
	m_window->draw(m_player.getBody());
	m_window->draw(m_kid.getBody());
	//m_window->draw(m_kid.getBodyTarget());


	for (auto& obstacle : m_obstacles) {
		m_window->draw(obstacle.getBody());
	}

	for (auto& wall : m_walls) {
		m_window->draw(wall.getBody());
	}


	m_window->display();
}

void GameplayScene::checkPlayerPosition()
{
	// The levels are a 4x4 box; if we go out of bounds, we should go to the adjacent level
	auto pos = m_player.getPosition();

	if (pos.x < 0.f) {
		// If we're not along the left bounds
		if (m_currentLevel % 4 != 0) {
			--m_currentLevel;
			setLevel(m_currentLevel);
			m_player.setPosition(pos + sf::Vector2f{RESOLUTION.x, 0.f});
		} 
	}
	else if (pos.x > RESOLUTION.x) {
		// If we're not along the right bounds
		if ((m_currentLevel - 3) % 4) {
			++m_currentLevel;
			setLevel(m_currentLevel);
			m_player.setPosition(pos - sf::Vector2f{RESOLUTION.x, 0.f});
		}
	}
	else if (pos.y < 0) {
		// If we're not in the top row
		if (m_currentLevel > 3) {
			m_currentLevel -= 4;
			setLevel(m_currentLevel);
			m_player.setPosition(pos + sf::Vector2f{0.f, RESOLUTION.y});
		}
	}
	else if (pos.y > RESOLUTION.y) {
		// If we're not in the bottom row
		if (m_currentLevel < 12) {
			m_currentLevel += 4;
			setLevel(m_currentLevel);
			m_player.setPosition(pos - sf::Vector2f{0.f, RESOLUTION.y});
		}
	}
}

void GameplayScene::setLevel(int t_level)
{
	m_currentLevel = t_level;

	m_obstacles.clear();

	sf::Vector2f offset = RESOLUTION / 32.f;

	for (sf::Vector2i& pos : m_levelData[m_currentLevel]) {
		float xPos = (RESOLUTION.x / 16.f) * pos.x;
		float yPos = (RESOLUTION.y / 16.f) * pos.y;

		m_obstacles.push_back(Obstacle({ xPos + offset.x, yPos + offset.y }, 20.f));
	}

	m_walls.clear();

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (i == 0 || i == 15 || j == 0 || j == 15) {
				float xPos = (RESOLUTION.x / 16.f) * i;
				float yPos = (RESOLUTION.y / 16.f) * j;

				m_walls.push_back(Obstacle({ xPos + offset.x, yPos + offset.y }, 20.f));
			}
		}
	}
}
//tbc
void GameplayScene::loadAudio()
{
	AudioHandler* handler = AudioHandler::getInstance();

	tracks[0] = { "again_seriously" };
	tracks[1] = { "are_you_even_listening" };
	tracks[2] = { "dont_leave_me_here" };
	tracks[3] = { "im_lonely" };
	tracks[4] = { "inspect" };
	tracks[5] = { "pssst" };
	tracks[6] = { "say_no" };
	tracks[7] = { "spiders" };
	tracks[8] = { "taking_so_long" };
	tracks[9] = { "you_found_me" };
	tracks[10] = { "you_will_come_back" };

	for (int i = 0; i < NUM_AUDIO; i++)
	{
		handler->loadSoundBuffer(tracks[i], tracks[i]);
	}
	
}

void GameplayScene::playRandomAudio()
{
	AudioHandler* handler = AudioHandler::getInstance();
	int num = rand() % NUM_AUDIO;
	handler->play(tracks[num]);
}
