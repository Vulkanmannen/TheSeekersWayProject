#ifndef INCLUDED_Lever
#define INCLUDED_Lever

#include "Block.h"
#include "Animation.h"

class Lever: public Block
{
public:

	Lever(sf::Vector2f &position, Block* target);
	~Lever();
	Block* mBlock;

	void render();
	void update();
	sf::Sprite getSprite();

	void Activate();

	bool mDrawn;
private:
	Animation mAnimation;
};

#endif