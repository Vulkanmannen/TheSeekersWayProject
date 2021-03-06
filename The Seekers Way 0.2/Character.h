#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "Animation.h"
#include "SFML\Graphics.hpp"
#include "Entity.h"
#include <SFML/Audio.hpp>

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
	sf::Vector2f getMovementSpeed()const;
	void setIsHitToFalse();
	void setStatusIdle();

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
	sf::Clock mAnimationClock;
	
	//-----------------funktioner som reglerar hur karakt�rerna r�r sig
	virtual void move();
	void jump();
	void jumping();
	void walk();
	void dontWalk(EntityKind &currentEntity);
	virtual void falling();
	virtual void fall();
	void slowdownPushBack();
	void hurtTime();
	void canMoveTime();
	virtual void takeDamage();
	void takeDamageFromArrow();
	void takeLavaDamage();

	// variabler som reglerar hur karakt�rerna r�r sig
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

	// variabler som styr hur karakt�ren beter sig vid skada
	bool mIsHit;
	bool mHurt;
	int mHurtCount;
	int mHurtTime;
	bool mCanMove;
	int mCanMoveCount;
	int mCanMoveTime;

	// hurt
	sf::Shader mHurtShader;
	sf::Clock mHurtClock;
	bool mHurtShow;

	// sound
	int mJumpSound;
	void playJumpSound();
};

#endif