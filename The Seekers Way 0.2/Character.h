#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "Animation.h"
#include "SFML\Graphics.hpp"
#include "Entity.h"

class Character: public Entity
{

public:
	Character();
		void onblock();

	~Character();
protected:

	enum Status
	{
		IDLE,
		WALK,
		JUMP,
		JUMPING,
		ACTION1,
		ACTION2
	};


	Status mStatus;
	bool mDirLeft;

	sf::Vector2f mMovementSpeed;

	void move();
	void jump();
	void walk();
	void falling();

	float mJumpTime;
	float mMaxRun;
	float mMaxJump;
	float mAcceleration;
	float mDecrease;
	float mGravity;
	float mJump;
	float mRun;
	float mJumping; 

	bool mFalling;
	bool mIsJumping;
};

#endif
