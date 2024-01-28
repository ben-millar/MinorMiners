#include "IBaseScene.h"
#include "Globals.h"
#include "SceneManager.h"

#include "TextureHandler.h"


class SplashScreen :
    public IBaseScene
{
public:
    SplashScreen();
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

    sf::Text m_text;
    TextureHandler* m_textures;
};