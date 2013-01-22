#include "Character.h"
#include "Entity.h"

const static float RUNSPEED =		0;
const static float MAXRUNSPEED =	0;


Character::Character(sf::Vector2f &getPosition):
	mPosition(getPosition),
	mMovementSpeed(2, 0),
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
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
}

// Knapptryck tas in och movementspeed ändras
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
