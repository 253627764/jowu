#ifndef AUDIO_H_
#define AUDIO_H_
#include <string>

class Audio
{
public:
	static Audio* instance();
	bool playMusic(const std::string &);
	bool playEffect(const std::string &);

private:
	Audio() {}

private:
	static Audio* s_instance;
};

#endif