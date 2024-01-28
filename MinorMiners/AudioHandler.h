#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include <map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class AudioHandler
{
public:
	static AudioHandler* getInstance() {
		static AudioHandler instance;
		return &instance;
	}

	void operator=(AudioHandler& const) = delete;
	AudioHandler(AudioHandler& const) = delete;

	void loadSoundBuffer(std::string t_fileName, std::string t_key)
	{
		sf::SoundBuffer buffer;

		if (!buffer.loadFromFile("assets\\VoiceLines\\" + t_fileName + ".wav"))
		{//error message
			std::cout << "problem loading sound" << std::endl;
		}

		m_audioMap.insert({ t_key, buffer });
		m_audio.setBuffer(buffer);
		m_keys.push_back(t_key);
	}

	sf::SoundBuffer getSoundBuffer(std::string t_key) {
		if (m_audioMap.count(t_key) == 0) 
			throw std::runtime_error("That sound doesn't exist, soz :(");

		return m_audioMap.find(t_key)->second;
	}

	void play(std::string t_key)
	{
		m_audio.setBuffer(m_audioMap.find(t_key)->second);
		m_audio.play();
	}

	void playRandom()
	{
		this->play(m_keys[rand()%m_keys.size()]);

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
	AudioHandler() {}

	sf::Sound m_audio;

	std::map<std::string, sf::SoundBuffer> m_audioMap;
	std::vector<std::string> m_keys;
};

#endif
