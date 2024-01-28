#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

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

	sf::Font* loadFont(std::string t_path, std::string t_key) {
		sf::Font* font = new sf::Font();

		if (!font->loadFromFile(t_path)) {
			std::cout << "Error loading: " + t_key + " at path: " + t_path << std::endl;
		}

		m_fontMap[t_key] = font;
		return font;
	}

	sf::Texture* getTexture(std::string t_key) {
		if (m_textureMap.find(t_key) != m_textureMap.end())
			return m_textureMap[t_key];

		return nullptr;
	}

	sf::Font* getFont(std::string t_key) {
		if (m_fontMap.find(t_key) != m_fontMap.end())
			return m_fontMap[t_key];

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
		loadTexture("assets/images/doorbottom.png", "doorBottom");

		loadTexture("assets/images/box.png", "box");
		loadTexture("assets/images/rock1.png", "rock1");
		loadTexture("assets/images/rock2.png", "rock2");
		
		loadTexture("assets/images/torch.png", "Torch");

		loadFont("assets/Font/OpenSans.ttf", "Font");
	}

	TextureHandler(TextureHandler& const t_textureHandler) = delete;

	std::unordered_map<std::string, sf::Texture*> m_textureMap;
	std::unordered_map<std::string, sf::Font*> m_fontMap;
};