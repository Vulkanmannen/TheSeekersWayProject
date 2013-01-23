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

	sf::Sprite getSprite();

protected:

	enum Status
	{
		IDLE,
		JUMP,
		JUMPING,
		FALLING,
		LANDING,
		ACTION1,
		ACTION2,
		WALK
	};

	Status mStatus;
	bool mDirLeft;

	sf::Vector2f mMovementSpeed;

	void move();
	void jump();
	void fall();
	void walk();
	void jumping();
	void falling();

	float mAcceleration;
	float mDecrease;
	float mGravity;
	float mJump;
	float mRun;

};

#endif
