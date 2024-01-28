#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "Door.h"
#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "Player.h"

#include "AudioHandler.h"

#include "TextureHandler.h"
#include "hammer.h"

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

    void setDoorStates();

    void renderFog();

    void updateFog();

    void checkPlayerPosition();

    void setLevel(int t_level);

    void loadAudio();

    void playRandomAudio();
    void loadLevelItems(int t_level);

    void unloadLevel();

    std::map<int, std::vector<sf::Vector2i>> m_levelData;
    std::vector<Obstacle> m_obstacles;
    std::vector<sf::FloatRect> m_obstacleColliders;
    std::array<DoorState, 16> m_doorStates;
    std::vector<Door> m_doors;

    candle::EdgeVector m_edges;
    candle::LightingArea m_fog;

    std::vector <candle::RadialLight*> m_lightSources;
    std::vector<Tool*> m_environmentTools;

    int m_currentLevel{ 4 };

    Player m_player;
    Enemy m_kid;
    static int const NUM_AUDIO = 11;
    std::string tracks[NUM_AUDIO];


    sf::Sprite m_background; 

    sf::Texture m_backgroundTexture;

    bool m_fogEnabled{false};
    TextureHandler* m_textures;

    std::vector<std::pair<Tool*, int>> m_toolsToLevels;
};

#endif

