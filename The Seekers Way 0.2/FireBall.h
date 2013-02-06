#ifndef INCLUDED_FIREBALL
#define INCLUDED_FIREBALL
#include "Block.h"
#include "Animation.h"

class FireBall: public Block
{
public:
	FireBall(sf::Vector2f &position);
	~FireBall();

	void render();
	void update(EntityKind &currentEntity);

protected:

	Animation mAnimation;
};

#endif