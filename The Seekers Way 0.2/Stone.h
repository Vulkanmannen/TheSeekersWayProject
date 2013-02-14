#ifndef INCLUDED_Stone
#define INCLUDED_Stone

#include "Block.h"
#include "SFML\Graphics.hpp"


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
	sf::Vector2f mMovementSpeed;
	float mDecrease;
	float mGravity;

	bool mFalling;
	bool mRblock;
	bool mLblock;
	bool mUblock;
	bool mDblock;

	bool mOnBlock;
};

#endif