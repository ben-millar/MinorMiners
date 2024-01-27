#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include <SFML/Graphics.hpp>

class IBaseScene
{
public:
	IBaseScene() = default;
	virtual ~IBaseScene() = default;

	/// <summary>
	/// Set the render window to be used by the scene
	/// </summary>
	/// <param name="t_window"></param>
	virtual void setWindow(sf::RenderWindow* t_window) { m_window = t_window; }

	/// <summary>
	/// Handles system events (input, etc)
	/// </summary>
	virtual void processEvents() = 0;

	/// <summary>
	/// Called once every game tick
	/// </summary>
	/// <param name="t_dT">Time in seconds since the last game update</param>
	virtual void update(sf::Time t_dT) = 0;

	/// <summary>
	/// Draw to our stored game window
	/// </summary>
	virtual void render() = 0;

protected:

	sf::RenderWindow* m_window;
};

#endif BASE_SCENE_H
