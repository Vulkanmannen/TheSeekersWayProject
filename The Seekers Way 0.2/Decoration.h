#ifndef INCLUDED_DECORATION
#define INCLUDED_DECORATION

#include "SFML\Graphics.hpp"
#include "Object.h"

class Decoration: public Object
{
public:
	Decoration(sf::Vector2f Position, unsigned char spriteNumber, bool bigDecoration = false);
	~Decoration();

	void update(EntityKind &currentEntity);
};

#endif