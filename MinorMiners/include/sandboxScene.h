#pragma once

#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "Torch.h"
#include "Toolbelt.h"
#include "Player.h"

#include "Candle/LightingArea.hpp"

#include <vector>

class sandboxScene :
    public IBaseScene
{
public:
    sandboxScene();
    ~sandboxScene() = default;

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
    Toolbelt m_playerBelt;

    candle::EdgeVector m_edges;
    candle::LightingArea m_fog;
    Torch* m_torch;

    std::vector <candle::RadialLight*> m_lightSources;

    Player m_player;
};
