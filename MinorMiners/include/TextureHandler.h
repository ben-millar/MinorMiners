#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureHandler
{
public: 
	static TextureHandler* getInstance() {
		static TextureHandler instance;
		return &instance;
	}

	~TextureHandler() = default;

	sf::Texture* loadTexture(std::string t_path, std::string t_key) {
		sf::Texture* texture = new sf::Texture();

		if (!texture->loadFromFile(t_path)) {
			std::cout << "Error loading: " + t_key + " at path: " + t_path << std::endl;
		}

		m_textureMap[t_key] = texture;
		return texture;
	}

	sf::Texture* getTexture(std::string t_key) {
		if (m_textureMap.find(t_key) != m_textureMap.end())
			return m_textureMap[t_key];

		return nullptr;
	}

private:
	TextureHandler() {
		loadTextures();
	};

	void loadTextures() {
		loadTexture("assets/images/bg.png", "Background");
		loadTexture("assets/images/moveLeft.png", "PlayerMoveLeft");
		loadTexture("assets/images/moveRight.png", "PlayerMoveRight");
		loadTexture("assets/images/spritewalk.png", "playerMoveVertical");

		loadTexture("assets/images/doorleft.png", "doorLeft");
		loadTexture("assets/images/doorright.png", "doorRight");
		loadTexture("assets/images/doortop.png", "doorTop");

		loadTexture("assets/images/box.png", "box");
		loadTexture("assets/images/rock1.png", "rock1");
		loadTexture("assets/images/rock2.png", "rock2");
	}

	TextureHandler(TextureHandler& const t_textureHandler) = delete;

	std::unordered_map<std::string, sf::Texture*> m_textureMap;
};