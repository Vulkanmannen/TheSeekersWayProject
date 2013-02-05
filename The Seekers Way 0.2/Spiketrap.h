#ifndef INCLUDED_SPIKETRAP
#define INCLUDED_SPIKETRAP
#include "Block.h"


class Spiketrap: public Block
{
public: 
	Spiketrap(sf::Vector2f &position);
	~Spiketrap();
};

#endif