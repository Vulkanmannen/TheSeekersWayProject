#ifndef INCLUDED_Arrow
#define INCLUDED_Arrow
#include "Animation.h"
#include "Object.h"

class Arrow: public Object
{
public:
	Arrow(sf::Vector2f &position, bool dirleft = true);
	~Arrow();
	void interact(Entity* e);
	void update(EntityKind &currentEntity);

	void killArrow();

private:
	Animation mAnimation;

	sf::Clock mShottingTime;
	sf::Vector2f mMovementSpeed;

	sf::Clock mArrowBrokenClock;

	bool mDirLeft;
	bool mWhole;
	bool mArrowBroken;
};

#endif