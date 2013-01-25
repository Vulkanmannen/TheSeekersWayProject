#ifndef INCLUDED_Door
#define INCLUDED_Door

#include "Block.h"

class Door: public Block
{
public:
	Door(sf::Vector2f &position);
	~Door();
	void open();
	void close();
	void Activate();
	void DisActivate();
};

#endif