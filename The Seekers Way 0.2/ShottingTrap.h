#ifndef INCLUDED_ShottingTrap
#define INCLUDED_ShottingTrap
#include "Animation.h"
#include "Block.h"
#include "EntityManager.h"

class ShottingTrap: public Block
{
public:
	ShottingTrap(sf::Vector2f &position);
	~ShottingTrap();

	void update();
	sf::Sprite getSprite();

	void Activate();
	void DisActivate();
};

#endif