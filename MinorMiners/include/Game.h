#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "GameplayScene.h"
#include "sandboxScene.h"
#include "Globals.h"
#include "SceneManager.h"


class Game
{
public:
	Game() = default;
	~Game() = default;

	void run();

	void loadTextures();

private:
	sf::RenderWindow* createWindow(std::string t_title);


	sf::RenderWindow* m_window{ nullptr };

};

#endif GAME_H
