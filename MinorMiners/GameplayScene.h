#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "Player.h"

#include "Candle/LightingArea.hpp"

class GameplayScene :
    public IBaseScene
{
public:
    GameplayScene();
    ~GameplayScene();

    /// <summary>
    /// Handles system events (input, etc.)
    /// </summary>
    virtual void processEvents() override;

    /// <summary>
    /// Called once every game tick
    /// </summary>
    /// <param name="t_dTime">Time in seconds since the last update</param>
    virtual void update(sf::Time t_dT) override;

    /// <summary>
    /// Draw the game to the render window
    /// </summary>
    virtual void render() override;

private:

    void renderFog();

    void updateFog();

    void checkPlayerPosition();

    void setLevel(int t_level);

    void loadTextures();

    std::map<int, std::vector<sf::Vector2i>> m_levelData;
    std::vector<Obstacle> m_walls;
    std::vector<Obstacle> m_obstacles;

    candle::EdgeVector m_edges;
    candle::LightingArea m_fog;

    std::vector <candle::RadialLight*> m_lightSources;

    int m_currentLevel{ 0 };

    Player m_player;
    Enemy m_kid;

    sf::Sprite m_background; 

    sf::Texture m_backgroundTexture;
};

#endif

