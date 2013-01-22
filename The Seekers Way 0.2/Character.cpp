#include "Character.h"
#include "Entity.h"

const static float RUNSPEED =		0;
const static float MAXRUNSPEED =	0;


Character::Character():
	mPosition(),
	mMovementSpeed(),
	mDirection(),
	mAcceleration(),
	mJumping(),
	mFalling(),
	mAlive(),
{	
}	

Character::~Character()
	{}


void Character::update()
{

}

// Flyttar Character
void Character::move()
{
	mPosition += mMovementSpeed;
}

// Knapptryck tas in och movementspeed ändras
void Character::walk()
{

}

// aktiverar så att man kan hoppa
void Character::jump()
{

}

// aktiverar så att man faller
void Character::fall()
{

}

// gör så att man hoppar med knapptryck
void Character::jumping()
{

}

// Gör så att man faller vid aktivition av fall
void Character::falling()
{

}
