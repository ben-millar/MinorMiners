#ifndef AUDIO_HANDLER.H
#define AUDIO_HANDLER.H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class AudioHandler
{
public:
	void loadAudio(std::string t_fileName)
	{
		if (!m_buffer.loadFromFile("assets\\VoiceLines\\" + t_fileName + ".wav"))
		{//error message
			std::cout << "problem loading sound" << std::endl;
		}
		m_audio.setBuffer(m_buffer);
	}

	void play()
	{
		m_audio.play();
	}

	void setAudio(bool t_bool)
	{
		m_audio.setLoop(t_bool);
	}
	/*
	AudioHandler* getAudio(std::string t_fileName)
	{
		AudioHandler audio(t_fileName);
		return& audio;
	}*/

private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_audio;
};

#endif
