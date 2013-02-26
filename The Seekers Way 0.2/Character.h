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

	virtual void update(EntityKind &currentEntity);

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
		ACTION1,
		ACTION2,
		ACTION3,
		ACTION4,
		ACTION5
	};
	
	Status mStatus;
	bool mDirLeft;

	sf::Vector2f mMovementSpeed;

	Animation mAnimation;
	
	//-----------------funktioner som reglerar hur karaktärerna rör sig
	virtual void move();
	void jump();
	void jumping();
	void walk();
	void dontWalk(EntityKind &currentEntity);
	void falling();
	virtual void fall();
	void slowdownPushBack();
	void hurtTime();
	void canMoveTime();
	virtual void takeDamage();
	void takeDamageFromArrow();

	// variabler som reglerar hur karaktärerna rör sig
	float mJumpTime;
	float mMaxRun;
	float mMaxJump;
	float mAcceleration;
	float mDecrease;
	float mGravity;
	float mJump;
	float mRun;
	float mJumping; 
	float mMaxSpeed;
	bool mFalling;
	bool mIsJumping;
	bool mCanPressJump;

	// variabler som styr hur karaktären beter sig vid skada
	bool mIsHit;
	bool mHurt;
	int mHurtCount;
	int mHurtTime;
	bool mCanMove;
	int mCanMoveCount;
	int mCanMoveTime;
	
	sf::Shader mHurtShader;
	sf::Clock mHurtClock;
	bool mHurtShow;
};

#endif