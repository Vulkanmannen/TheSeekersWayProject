#ifndef INCLUDED_Door
#define INCLUDED_Door

#include "DecorateBlock.h"

class Door: public DecorateBlock
{
	Door(Block *b);
	~Door();
};

#endif