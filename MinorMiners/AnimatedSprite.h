#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

enum class State : uint8_t{
	NONE, 
	Standing, 
	Walking_right, 
	Walking_left, 
	Walking_down
};

namespace sf {

	struct TextureInfo {
		TextureInfo() : tex(nullptr), frames(0) {}
		TextureInfo(sf::Texture* t_tex, int t_frames) : tex(t_tex), frames(t_frames) {}
		sf::Texture* tex;
		int frames;
	};

	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite() = default;
		AnimatedSprite(int t_rows, float t_frameDelay, IntRect t_frameSize) :
			m_frameDelay(t_frameDelay) {};

		void setFramteDelay(float t_frameDelay) {
			m_frameDelay = t_frameDelay;
		}

		void update(Time t_dt);

		void setState(State t_state) {
			if (m_states.find(t_state) == m_states.end())
				return;

			if (m_currentState == t_state)
				return;

			m_currentTexture = m_states[t_state];
			sf::Vector2i size = static_cast<sf::Vector2i>(m_currentTexture.tex->getSize());
			int frames = (t_state == State::Standing) ? 3 : m_currentTexture.frames;
			m_size = { 0,0, size.x / frames, size.y };

			setTexture(*m_currentTexture.tex);
			setTextureRect(m_size);
			m_currentState = t_state;
		}

		void initTexture(State t_state, Texture* t_texture, int t_frames) {
			m_states[t_state] = { t_texture, t_frames };
		}
	private:
		float m_frameDelay{ 0 }, m_frameCounter{ 0 };
		int m_current{ 0 };
		IntRect m_size;

		std::unordered_map<State, TextureInfo> m_states;

		TextureInfo m_currentTexture;

		State m_currentState = State::NONE;
	};

}