#ifndef INCLUDED_SPIKETRAP
#define INCLUDED_SPIKETRAP
#include "Object.h"
#include "Animation.h"

class Spiketrap: public Object
{
public: 
	Spiketrap(sf::Vector2f &position);
	~Spiketrap();

	void render();
	void update(EntityKind &currentEntity);

protected:

	enum SpikeStatus
	{
		START,
		DOWN
	};

	SpikeStatus mSpikeStatus;

	Animation mAnimation;

	sf::Clock mClock;

	void SpikeMove();

	int mSpikeAcc;
	float mMaxSpikeHeight;
	float mMinSpikeHeight;

};

#endif