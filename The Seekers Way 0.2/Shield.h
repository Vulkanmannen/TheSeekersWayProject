#ifndef INCLUDED_SHIELD
#define INCLUDED_SHIELD
#include "Animation.h"
#include "Object.h"
#include "SFML\System.hpp"

class Shield: public Object
{
public:
	Shield(sf::Vector2f &position, bool dirLeft);

	~Shield();

	void render();
	void update(EntityKind &currentEntity);
	int GetShieldCount()const;
	void interact(Entity* e);

	bool getEndOfAnimation()const;

	void setToDead();

private:
	Animation mAnimation;
	int mShieldCount;
	bool mDirLeft;

	bool mOpen;
	bool mDead;
	sf::Clock mClock;
	
};

#endif