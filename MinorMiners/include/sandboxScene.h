#pragma once

#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "Torch.h"
#include "Toolbelt.h"

#include "Candle/LightingArea.hpp"

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
    sf::RectangleShape m_rect;
    sf::RectangleShape m_hiddenRect;

    candle::EdgeVector m_edges;
    candle::LightingArea m_fog;
    Torch* m_torch;

    sf::Sprite m_sprite;
    sf::Texture m_tex;
};
