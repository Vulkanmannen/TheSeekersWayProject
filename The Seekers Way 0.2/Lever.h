#ifndef INCLUDED_Lever
#define INCLUDED_Lever

#include "Block.h"
#include "Door.h"

class Lever: public Block
{
public:

	Lever(sf::Vector2f &position, int id);
	~Lever();
	Block* mBlock;

	void Activate();

	bool mDrawn;
};

#endif