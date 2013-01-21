#include "Character.h"

const static float RUNSPEED =		0;
const static float MAXRUNSPEED =	0;


Character::Character(sf::Vector2f &position)
{
	mPosition(position);
	mMove();
	mJump();
	mJumping(true);
	mFalling(false);
}


Character::~Character()
	{}

