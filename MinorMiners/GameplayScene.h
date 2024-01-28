#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "Player.h"
#include "AudioHandler.h"

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

    void checkPlayerPosition();

    void setLevel(int t_level);

    void loadAudio();

    void playRandomAudio();

    std::map<int, std::vector<sf::Vector2i>> m_levelData;
    std::vector<Obstacle> m_walls;
    std::vector<Obstacle> m_obstacles;

    int m_currentLevel{ 0 };

    Player m_player;
    Enemy m_kid;
    static int const NUM_AUDIO = 11;
    std::string tracks[NUM_AUDIO];

};

#endif

