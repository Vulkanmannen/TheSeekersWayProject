#include "Character.h"
#include "Entity.h"

const static float RUNSPEED =		0;
const static float MAXRUNSPEED =	0;

<<<<<<< HEAD
<<<<<<< HEAD


Character::Character(sf::Vector2f &getPosition):
	mPosition(getPosition),
	mMovementSpeed(2, 0),
=======
=======
>>>>>>> master
Character::Character():
	mPosition(),
	mMovementSpeed(),
>>>>>>> master
	mDirection(),
	mAcceleration(0.5),
	mDecrease(0.5),
	mAlive(true),
	mGravity(5.0)
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
<<<<<<< HEAD
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
=======
	mPosition += mMovementSpeed;

<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
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
