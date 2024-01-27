#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "IBaseScene.h"
#include "Globals.h"

enum class SceneType { GAMEPLAY };

using Scene = std::unique_ptr<IBaseScene>;
using SceneFactory = std::unordered_map<SceneType, std::function<Scene()>>;

class SceneManager
{
public:
	static SceneManager* getInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void setWindow(sf::RenderWindow* t_window) { m_window = t_window; }

	template<typename T, typename... A>
	void registerScene(SceneType t_sceneType, const A& ...args)
	{
		m_sceneFactory.emplace(t_sceneType, [args...]() {
			return std::make_unique<T>(args...);
			});
	}

	void setScene(SceneType t_sceneType)
	{
		if (const auto it = m_sceneFactory.find(t_sceneType); it != m_sceneFactory.end())
		{
			m_currentScene = it->second();
			m_currentScene->setWindow(m_window);
		} 
		else
		{
			std::cerr << ERROR_MSG << std::endl;
		}
	}

	void processEvents() { m_currentScene->processEvents(); }
	void update(sf::Time t_dT) { m_currentScene->update(t_dT); }
	void render() { m_currentScene->render(); }

private:
	SceneManager() {}
	SceneFactory m_sceneFactory;
	Scene m_currentScene;
	sf::RenderWindow* m_window{ nullptr };

	const std::string ERROR_MSG{
		"Trying to create scene which hasn't been registered with SceneManager"
	};

};

#endif

