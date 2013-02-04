#ifndef INCLUDED_KIBA
#define INCLUDED_KIBA

#include "Character.h"
#include "SFML\Graphics.hpp"
#include "Stone.h"

class Kiba: public Character
{
public:
	Kiba(sf::Vector2f &position);
	~Kiba();
	
	void telekinesis();
	void update(EntityKind &currentEntity);
	void render();

private:
	Stone *mStone;
};

#endif