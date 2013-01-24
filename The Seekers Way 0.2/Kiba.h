#ifndef INCLUDED_KIBA
#define INCLUDED_KIBA

#include "Character.h"
#include "SFML\Graphics.hpp"

class Kiba: public Character
{
public:
	Kiba(sf::Vector2f &position);
	~Kiba();
	
	void update();
	sf::Sprite getSprite();

private:
	Animation mAnimation;
};

#endif