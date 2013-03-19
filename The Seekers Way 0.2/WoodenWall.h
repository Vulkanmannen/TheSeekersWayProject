#ifndef INCLUDED_WoodenWall
#define INCLUDED_WoodenWall

#include "Animation.h"
#include "Block.h"

class WoodenWall : public Block
{
public:
	WoodenWall(sf::Vector2f &position);
	~WoodenWall();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

	void Activate();
private:
	Animation mAnimation;
	sf::Clock mAnimationClock;

	bool mHit;
};

#endif