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

	static sf::Clock mClockFrame;
	static sf::Clock mClockWait;
	static float mTimeToNextFrame;
	static float mTimeDown;

	void SpikeMove();
	static void spikeCount();

	static int mSpikeCount;
	static bool mCountDirectionUpp;
	static bool mWait;
	static bool mHurting;
	float mStartYValue;
};

#endif