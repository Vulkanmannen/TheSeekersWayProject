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
	void update();
	sf::Sprite getSprite();

	void Activate();
	void DisActivate();
	
private:
	Animation mAnimation;
};

#endif