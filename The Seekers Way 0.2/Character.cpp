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

// Knapptryck tas in och movementspeed �ndras
void Character::walk()
{

}

// aktiverar s� att man kan hoppa
void Character::jump()
{

}

// aktiverar s� att man faller
void Character::fall()
{

}

// g�r s� att man hoppar med knapptryck
void Character::jumping()
{

}

// G�r s� att man faller vid aktivition av fall
void Character::falling()
{

}
