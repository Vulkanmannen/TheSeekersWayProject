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

	virtual void onblock();
	void hitBlockFromBelow();

	virtual void interact(Entity* e);

	bool getIsHit()const;
	void setIsHitToFalse();
protected:

	enum Status
	{
		IDLE,
		WALK,
		JUMP,
		INAIR,
		HURT,
		ACTION1,
		ACTION2,
		ACTION3
	};
	
	Status mStatus;
	bool mDirLeft;

	sf::Vector2f mMovementSpeed;

	Animation mAnimation;

	virtual void move();
	void jump();
	void jumping();
	void walk();
	void dontWalk(EntityKind &currentEntity);
	void falling();
	void fall();

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

	bool mIsHit;
};

#endif