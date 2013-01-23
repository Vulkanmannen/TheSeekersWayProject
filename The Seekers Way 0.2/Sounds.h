#ifndef INCLUDED_SOUND
#define INCLUDED_SOUND
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <map>

class Sounds
{
public:

	~Sounds();
	static Sounds* getInstance();
	void Play(std::string namn);
	void Play(std::string namn, float volume);
	void Loop(std::string namn);
	void Loop(std::string namn, float volume);
	void StopAll();
	void PauseAll();
	void UnPauseAll();
	void setMasterVolume(float volume);
	float getMasterVolume();
	sf::SoundBuffer getBuffer(std::string namn);

private:
	
	Sounds();
	static Sounds *sInstance;
	typedef std::vector<sf::Sound*> SoundVector;
	SoundVector mSounds;
	typedef std::map<std::string, sf::SoundBuffer*> BufferMap;
	BufferMap bufferlista;
	void Playbase(std::string namn, float volume, bool repeat);
};

#endif