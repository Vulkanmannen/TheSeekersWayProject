#ifndef INCLUDED_BigBridge
#define INCLUDED_BigBridge
#include "Animation.h"
#include "Block.h"

class BigBridge: public Block
{
public:
	BigBridge(sf::Vector2f &position, bool closed = true);
	~BigBridge();

	void render();	
	void update(EntityKind &currentEntity);
	void interact(Entity* e);

	sf::Sprite getSprite();

	void Activate();
	void DisActivate();
	
private:
	Animation mAnimation;
	sf::Clock mAnimationClock;
	sf::Clock mSoundClock;

	bool isitclosed;

	enum Status {CLOSED, OPENING, OPEN, CLOSING};	
	Status mStatus;
};

#endif