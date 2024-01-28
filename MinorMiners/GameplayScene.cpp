#include "GameplayScene.h"

GameplayScene::GameplayScene() : 
	m_fog(candle::LightingArea::Mode::FOG, { 0.0f, 0.0f }, RESOLUTION)
{
	std::cout << "Creating " << typeid(*this).name() << std::endl;

	m_levelData = LevelLoader::getInstance()->load("assets/level_data/levels.json");

	setLevel(m_currentLevel);

	m_fog.setAreaColor(sf::Color::Black);

	m_lightSources.push_back(&m_player.getLight());
	m_textures = TextureHandler::getInstance();

	m_background.setTexture(*m_textures->getTexture("Background"));
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
	m_kid.move(t_dT);
	m_player.update(t_dT);

	for (auto& obstacle : m_obstacles) {
		m_player.collides(obstacle);
	}

	m_player.checkCollisions(m_obstacleColliders);

	checkPlayerPosition();

	bool checkWalls{ true };
	for (auto& door : m_doors) 
		if (door.getCollider().contains(m_player.getPosition())) checkWalls = false;

	if (checkWalls) m_player.checkInBounds();

	updateFog();
}

void GameplayScene::render()
{
	if (m_fogEnabled) renderFog();

	m_window->clear();

	// Draw your stuff here
	m_window->draw(m_player);
	m_window->draw(m_kid.getBody());
	//m_window->draw(m_kid.getBodyTarget());

	m_window->draw(m_background);

	for (auto& obstacle : m_obstacles) {
		m_window->draw(obstacle.getBody());
	}

	for (auto& door : m_doors) m_window->draw(door.getSprite());

	m_window->draw(m_player);

	m_window->draw(m_fog);


	m_window->display();
}

void GameplayScene::renderFog()
{
	m_fog.clear();
	for (auto light : m_lightSources)
		m_fog.draw(*light);

	m_fog.display();
}

void GameplayScene::updateFog()
{
	for (auto light : m_lightSources)
		light->castLight(m_edges.begin(), m_edges.end());
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

		m_obstacles.push_back(Obstacle({ xPos + offset.x, yPos + offset.y }));
		m_edges.emplace_back(sf::Vector2f{xPos, yPos}, sf::Vector2f{xPos + offset.x * 2, yPos}); // top left -> top right
		m_edges.emplace_back(sf::Vector2f{xPos + offset.x * 2, yPos}, sf::Vector2f{xPos + offset.x * 2, yPos + offset.y * 2}); // top right -> bottom right
		m_edges.emplace_back(sf::Vector2f{xPos, yPos + offset.y * 2}, sf::Vector2f{xPos + offset.x * 2, yPos + offset.y * 2}); // bottom left -> bottom right
		m_edges.emplace_back(sf::Vector2f{xPos, yPos}, sf::Vector2f{xPos, yPos + offset.y * 2}); // top left -> bottom left
	}

	static std::set<int> brightRooms{ 0,1,4,5 };
	m_fogEnabled = (!brightRooms.count(m_currentLevel));

	m_obstacleColliders.clear();
	for (auto& obstacle : m_obstacles) {
		m_obstacleColliders.push_back(obstacle.getBody().getGlobalBounds());
	}

	m_doors.clear();
	DoorState doorState = m_doorStates[m_currentLevel];

	static float bufferPx{ 80.f };
	if (doorState.north) m_doors.push_back(Door({ RESOLUTION.x / 2.f, bufferPx }));
	if (doorState.south) m_doors.push_back(Door({ RESOLUTION.x / 2.f, RESOLUTION.y - bufferPx }));
	if (doorState.east) m_doors.push_back(Door({ RESOLUTION.x - bufferPx, RESOLUTION.y / 2.f }));
	if (doorState.west) m_doors.push_back(Door({ bufferPx, RESOLUTION.y / 2.f }));
}
