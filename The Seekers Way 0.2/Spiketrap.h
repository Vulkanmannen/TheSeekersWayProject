#ifndef INCLUDED_SPIKETRAP
#define INCLUDED_SPIKETRAP

#include "Block.h"
#include "Object.h"
#include "Animation.h"

class Spiketrap: public Object
{
public: 
	Spiketrap(sf::Vector2f &position);
	~Spiketrap();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

	bool getHurting()const;

private:
	Animation mAnimation;

	sf::Clock mClockFrame;
	sf::Clock mClockWait;
	float mTimeToNextFrame;
	float mTimeDown;

	void SpikeMove();
	void spikeCount();

	int mSpikeCount;
	bool mCountDirectionUpp;
	bool mWait;
	bool mHurting;
	float mStartYValue;
};

#endif