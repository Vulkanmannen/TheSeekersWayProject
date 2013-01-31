#ifndef INCLUDED_Block
#define INCLUDED_Block

#include "Entity.h"
#include "SFML\Graphics.hpp"



class Block: public Entity
{
public:
	Block();
	virtual ~Block();
	
	virtual void interact(Entity* e);
	virtual void Activate();
	virtual void DisActivate();
};

#endif