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

bool Audio::playEffect(char* path)
{
	if (!checkPath(path)) return false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path);
	return true;
}

bool Audio::playMusic(char *path)
{
	if (!checkPath(path)) return false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(path);
	return true;
}

bool Audio::checkPath(const std::string& path)
{
	return true;
}
