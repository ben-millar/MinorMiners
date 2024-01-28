#include "GameplayScene.h"

GameplayScene::GameplayScene() : 
	m_fog(candle::LightingArea::Mode::FOG, { 0.0f, 0.0f }, RESOLUTION)
{
	std::cout << "Creating " << typeid(*this).name() << std::endl;

	m_levelData = LevelLoader::getInstance()->load("assets/level_data/levels.json");

	m_toolsToLevels.push_back({ new Torch({200,200}), 0 });

	setDoorStates();

	setLevel(m_currentLevel);

	loadAudio();

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
			case sf::Keyboard::D:
				m_player.setDirectionX(0.0f);
				break;
			case sf::Keyboard::A:
				m_player.setDirectionX(0.0f);
				break;
			case sf::Keyboard::W:
				m_player.setDirectionY(0.0f);
				break;
			case sf::Keyboard::S:
				m_player.setDirectionY(0.0f);
				break;
			case sf::Keyboard::E:
				if (auto iter = m_environmentTools.begin(); iter != m_environmentTools.end()) {
					m_player.addTool(*iter);

					for (auto toolIter = m_toolsToLevels.begin(); toolIter != m_toolsToLevels.end(); ++toolIter) {
						if (toolIter->first == *iter)
							if (toolIter->second == m_currentLevel) {
								m_toolsToLevels.erase(toolIter);
								break;
							}
					}
					m_environmentTools.erase(iter);
				}
				break;
			case sf::Keyboard::Q:
				if (auto tool = m_player.dropTool(); tool != nullptr) {
					m_environmentTools.push_back(tool);
					m_toolsToLevels.push_back({ tool, m_currentLevel });
				}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player.setDirectionY(-1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player.setDirectionY(1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player.setDirectionX(-1.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player.setDirectionX(1.0f);
	}

	for (auto& obstacle : m_obstacles) {
		m_player.collides(obstacle);
	}

	for (auto& tool : m_environmentTools) tool->update(t_dT, tool->getSprite().getPosition());

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
	renderFog();

	m_window->clear();
	m_window->draw(m_background);

	// Draw your stuff here
	m_window->draw(m_kid.getBody());

	for (auto& tool : m_environmentTools) m_window->draw(*tool);

	for (auto& obstacle : m_obstacles) m_window->draw(obstacle.getSprite());

	for (auto& door : m_doors) m_window->draw(door.getSprite());

	m_window->draw(m_player);
	for (auto& toolInBelt : m_player.getTools()) m_window->draw(*toolInBelt);
	//m_window->draw(m_player.getCollider());

	m_window->draw(m_fog);


	m_window->display();
}

void GameplayScene::setDoorStates()
{
	m_doorStates = { {
		DoorState(false, false, true, false),	// 1
		DoorState(false, true, false, true),	// 2
		DoorState(false, false, true, false),	// 3
		DoorState(false, true, false, true),	// 4
		DoorState(false, false, true, false),	// 5
		DoorState(true, false, true, true),		// 6
		DoorState(false, false, true, true),	// 7
		DoorState(true, true, false, true),		// 8
		DoorState(false, true, true, false),	// 9
		DoorState(false, true, false, true),	// 10
		DoorState(false, true, true, false),	// 11
		DoorState(true, false, false, true),	// 12
		DoorState(true, true, false, false),	// 13
		DoorState(true, false, true, false),	// 14
		DoorState(true, false, true, true),		// 15
		DoorState(false, false, false, true)	// 16
		} };
}

void GameplayScene::renderFog()
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

void GameplayScene::updateFog()
{
	for (auto light : m_lightSources)
		light->castLight(m_edges.begin(), m_edges.end());

	for (auto light : m_environmentTools)
		if (light->getType() == ToolType::TORCH)
			dynamic_cast<Torch*>(light)->getLight().castLight(m_edges.begin(), m_edges.end());

	if (m_player.getTorch()) {
		m_player.getTorch()->getLight().castLight(m_edges.begin(), m_edges.end());
	}
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
	unloadLevel();
	m_currentLevel = t_level;

	loadLevelItems(t_level);

	m_obstacles.clear();
	m_edges.clear();
		
	sf::Vector2f offset = RESOLUTION / 32.f;
	sf::Vector2f lightOffset = offset - sf::Vector2f{10.f, 10.f};

	for (sf::Vector2i& pos : m_levelData[m_currentLevel]) {
		float xPos = (RESOLUTION.x / 16.f) * pos.x;
		float yPos = (RESOLUTION.y / 16.f) * pos.y;

		m_obstacles.push_back(Obstacle({ xPos + offset.x, yPos + offset.y }));
		m_edges.emplace_back(sf::Vector2f{xPos, yPos}, sf::Vector2f{xPos + lightOffset.x * 2, yPos}); // top left -> top right
		m_edges.emplace_back(sf::Vector2f{xPos + lightOffset.x * 2, yPos}, sf::Vector2f{xPos + lightOffset.x * 2, yPos + lightOffset.y * 2}); // top right -> bottom right
		m_edges.emplace_back(sf::Vector2f{xPos, yPos + lightOffset.y * 2}, sf::Vector2f{xPos + lightOffset.x * 2, yPos + lightOffset.y * 2}); // bottom left -> bottom right
		m_edges.emplace_back(sf::Vector2f{xPos, yPos}, sf::Vector2f{xPos, yPos + lightOffset.y * 2}); // top left -> bottom left
	}

	static std::set<int> brightRooms{ 1,4,5 };
	if (brightRooms.count(m_currentLevel)) {
		m_fog.setAreaOpacity(0.4f); // BRIGHT
	}
	else {
		m_fog.setAreaOpacity(0.9f); // DARK
	}

	m_obstacleColliders.clear();
	for (auto& obstacle : m_obstacles) {
		m_obstacleColliders.push_back(obstacle.getBody().getGlobalBounds());
	}

	m_doors.clear();
	DoorState doorState = m_doorStates[m_currentLevel];

	auto tm = TextureHandler::getInstance();
	static float bufferPx{ 80.f };

	if (doorState.north) m_doors.push_back(Door({ RESOLUTION.x / 2.f, bufferPx }, tm->getTexture("doorTop")));
	if (doorState.south) m_doors.push_back(Door({ RESOLUTION.x / 2.f, RESOLUTION.y - bufferPx }, tm->getTexture("doorBottom")));
	if (doorState.east) m_doors.push_back(Door({ RESOLUTION.x - bufferPx, RESOLUTION.y / 2.f }, tm->getTexture("doorRight")));
	if (doorState.west) m_doors.push_back(Door({ bufferPx, RESOLUTION.y / 2.f }, tm->getTexture("doorLeft")));
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

void GameplayScene::loadLevelItems(int t_level)
{
	for (auto pair : m_toolsToLevels) {
		if (pair.second == t_level)
			m_environmentTools.push_back(pair.first);
	}
}

void GameplayScene::unloadLevel()
{
	m_environmentTools.clear();
}
