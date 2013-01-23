#ifndef INCLUDED_Block
#define INCLUDED_Block

#include "Entity.h"
#include "SFML\Graphics.hpp"



class Block: public Entity
{
public:
	Block();
	virtual ~Block();

	sf::Sprite getSprite();
protected:
	sf::Sprite mSprite;
};

#endif