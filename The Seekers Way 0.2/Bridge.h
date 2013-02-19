#ifndef INCLUDED_Bridge
#define INCLUDED_Bridge
#include "Animation.h"
#include "Block.h"

class Bridge: public Block
{
public:
	Bridge(sf::Vector2f &position, bool closed = true);
	~Bridge();

	void render();	
	void update(EntityKind &currentEntity);
	void interact(Entity* e);

	sf::Sprite getSprite();

	void Activate();
	void DisActivate();
	
private:
	Animation mAnimation;
	bool isitclosed;
};

#endif