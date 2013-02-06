#ifndef INCLUDED_FIRERUNE
#define INCLUDED_FIRERUNE
#include "Block.h"
#include "Animation.h"

class FireRune: public Block
{
public:
	FireRune(sf::Vector2f &position);
	~FireRune();

	void render();
	void update(EntityKind &currentEntity);

protected:

	enum FireTrapStatus
	{
		IDLE,
		CIRCLE
	};

	FireTrapStatus mFireTrapStatus;
	Animation mAnimation;
	sf::Clock mClock;

	void FireBallCircle();
};
#endif