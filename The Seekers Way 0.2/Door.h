#ifndef INCLUDED_Door
#define INCLUDED_Door
#include "Animation.h"
#include "Block.h"

class Door: public Block
{
public:
	Door(sf::Vector2f &position);
	~Door();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

	sf::Sprite getSprite();

	void Activate();
	void DisActivate();
	
private:
	Animation mAnimation;
};

#endif