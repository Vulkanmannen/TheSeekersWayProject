#ifndef INCLUDED_Door
#define INCLUDED_Door

#include "Animation.h"
#include "Block.h"
#include <string>

class Door: public Block
{
public:
	Door(sf::Vector2f &position, std::string &texture = std::string("door.png"));
	~Door();

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
	
	enum Status {CLOSED, OPENING, OPEN, CLOSING};
	int in;
	Status mStatus;

	bool mMagicDoor;
};

#endif