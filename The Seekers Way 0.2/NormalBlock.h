#ifndef INCLUDED_NormalBlock
#define INCLUDED_NormalBlock

#include "Block.h"
#include "SFML\Graphics.hpp"


class NormalBlock: public Block
{
public:
	NormalBlock(sf::Vector2f Position, unsigned char spriteNumber);
	~NormalBlock();
	void update(EntityKind &currentEntity);
};

#endif