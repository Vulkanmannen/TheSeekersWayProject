#include "Character.h"
#include "Entity.h"

const static float RUNSPEED =		0;
const static float MAXRUNSPEED =	0;


Character::Character():
	mMovementSpeed(2, 0),
<<<<<<< HEAD
	mAcceleration(0.5),
	mDecrease(0.5),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false)
=======
	mDirection(),
	mAcceleration(-0.5),
	mDecrease(0.5),
	mGravity(5.0),
	mJump(10.0)
>>>>>>> ameroz
{
	mAlive = true;
	mBaseKind = CHARACTER;
}

Character::~Character()
	{}


// Flyttar Character
void Character::move()
{
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
}

// Knapptryck tas in och movementspeed �ndras
void Character::walk()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mPosition -= mMovementSpeed;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mPosition += mMovementSpeed;
	}
}

// aktiverar s� att man kan hoppa
void Character::jump()
{
	if()
	{
	
	}
}

// aktiverar s� att man faller
void Character::fall()
{

}

// g�r s� att man hoppar med knapptryck
void Character::jumping()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump();
	}
}

// G�r s� att man faller vid aktivition av fall
void Character::falling()
{

}
