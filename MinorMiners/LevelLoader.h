#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <map>
#include <string>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class LevelLoader
{
public:
	static LevelLoader* getInstance()
	{
		static LevelLoader instance;
		return &instance;
	}

	std::map<int, std::vector<sf::Vector2i>> load(const char* t_path)
	{
		json j;

		loadFile(t_path, j);

		std::map<int, std::vector<sf::Vector2i>> levels;
		for (const auto& [level, boulders] : j[LEVELS].items()) {
			int levelNum = std::stoi(level);
			for (const auto& item : boulders) {
				sf::Vector2i boulder(item[X].get<int>(), item[Y].get<int>());
				levels[levelNum].push_back(boulder);
			}
		}

		return levels;
	}

private:
	const string LEVELS{ "levels" }, X{ "x" }, Y{ "y" };

	LevelLoader() {}

	void loadFile(const char* t_path, json& target) {
		std::ifstream file(t_path);
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file.");
		}

		try {
			file >> target;
		}
		catch (const json::parse_error& e) {
			throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
		}
	}
};

#endif