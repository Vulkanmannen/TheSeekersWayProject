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
	void onblock();

	virtual void interact(Entity* e);
	static void characterUpdate(Character* character, EntityKind &entityKind);

protected:

	enum Status
	{
		IDLE,
		WALK,
		JUMP,
		INAIR,
		ACTION1,
		ACTION2
	};
	
	Status mStatus;
	bool mDirLeft;

	sf::Vector2f mMovementSpeed;

	Animation mAnimation;

	void move(EntityKind &e);
	void jump();
	void walk();
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
};

#endif
