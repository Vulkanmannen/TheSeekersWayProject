#ifndef INCLUDED_DecorateBlock
#define INCLUDED_DecorateBlock

#include "Block.h"


class DecorateBlock: public Block
{
public:

	DecorateBlock();
	virtual ~DecorateBlock();
	Block* mBlock;

};

#endif