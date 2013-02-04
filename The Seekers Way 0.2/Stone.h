#ifndef INCLUDED_Stone
#define INCLUDED_Stone

#include "Block.h"
#include "SFML\Graphics.hpp"


class Stone: public Block
{
public:
	Stone(sf::Vector2f Position);
	~Stone();
	void update(EntityKind &currentEntity);
	void interact(Entity* e);

	void move();
	void falling();

private:
	sf::Vector2f mMovementSpeed;
	float mDecrease;
	float mGravity;

	bool mFalling;
};

#endif