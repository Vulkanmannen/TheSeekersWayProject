#ifndef INCLUDED_DECORATION
#define INCLUDED_DECORATION

#include "SFML\Graphics.hpp"
#include "Object.h"

class Decoration: public Object
{
public:
	Decoration(sf::Vector2f Position, unsigned char spriteNumber, bool bigDecoration = false, bool paralaxing = false, bool biggerDecoration = false);
	~Decoration();

	void update(EntityKind &currentEntity);
private:
	bool mParalaxing;
};

#endif