#include "SimpleAudioEngine.h"
#include "Audio.h"

Audio* Audio::s_instance = nullptr;

Audio* Audio::instance()
{
	if (!s_instance) {
		s_instance = new Audio;
	}

	return s_instance;
}

bool Audio::playEffect(const std::string& path)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());
	return true;
}

bool Audio::playMusic(const std::string& path)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str());
	return true;
}
