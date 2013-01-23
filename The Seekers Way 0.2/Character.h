#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "Animation.h"
#include "SFML\Graphics.hpp"
#include "Entity.h"

class Character: public Entity
{
public:
	Character();
	~Character();

protected:

	enum Status
	{
		IDLE,
		JUMP,
		JUMPING,
		FALL,
		LANDING,
		ACTION1,
		ACTION2,
		WALK
	};

	enum Direction
	{
		LEFT,
		RIGHT
	};

	Animation mAnimation;

	sf::Vector2f mMovementSpeed;
	sf::Vector2f mDirection;
	//sf::Vector2f mPosition;

	void move();
	void jump();
	void fall();
	void walk();
	void jumping();
	void falling();

	//bool mAlive;
	float mAcceleration;
	float mDecrease;
	float mGravity;
	float mJump;

};

#endif
