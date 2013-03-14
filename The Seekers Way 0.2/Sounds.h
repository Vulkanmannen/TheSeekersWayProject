#ifndef INCLUDED_SOUND
#define INCLUDED_SOUND
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <map>
#include "EntityManager.h"

class Sounds
{
public:

	~Sounds();
	static Sounds* getInstance();
	void Play(std::string namn, float volume = 100, sf::Vector2f position = EntityManager::getInstance()->getView()->getCenter());
	void Loop(std::string namn, float volume = 100, sf::Vector2f position = EntityManager::getInstance()->getView()->getCenter());
	void Stop(std::string namn);
	void Pause(std::string namn);
	void StopAll();
	void PauseAll();
	void UnPauseAll();
	void setMasterVolume(float volume);
	float getMasterVolume();
	sf::SoundBuffer* getBuffer(std::string namn);

private:
	int soundlimit;
	Sounds();
	static Sounds *sInstance;
	typedef std::vector<sf::Sound*> SoundVector;
	SoundVector mSounds;
	typedef std::map<std::string, sf::SoundBuffer*> BufferMap;
	BufferMap bufferlista;
	void Playbase(std::string namn, sf::Vector2f position, float volume, bool repeat);
};

#endif