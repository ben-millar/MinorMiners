#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "Player.h"

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

    Player m_player;
};

#endif

