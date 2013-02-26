#ifndef INCLUDED_Stone
#define INCLUDED_Stone

#include "Block.h"
#include "SFML\Graphics.hpp"
#include "Animation.h"


class Stone: public Block
{
public:
	Stone(sf::Vector2f Position);
	~Stone();
	void update(EntityKind &currentEntity);
	void render();
	void interact(Entity* e);

	void move();
	void falling();
	void telekinesis();
	void attraction();
	
	bool onblock();

	bool mtelekinesis;
	bool mtelemove;
	
	sf::Vector2f mKibaPos;

private:
	Animation mAnimation;

	sf::Vector2f mMovementSpeed;
	float mDecrease;
	float mGravity;
	float radius;
	bool mFalling;
	bool mRblock;
	bool mLblock;
	bool mUblock;
	bool mDblock;

	bool mOnBlock;

	bool mCanMove;
};

#endif