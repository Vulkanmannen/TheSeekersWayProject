#ifndef INCLUDED_VINE
#define INCLUDED_VINE

#include "SFML\Graphics.hpp"
#include "Block.h"

class Vine : public Block
{
public:
	Vine(sf::Vector2f &position, unsigned char spriteNumber);
	~Vine();

	void update(EntityKind &currentEntity);
};

#endif