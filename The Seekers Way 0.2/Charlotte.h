#ifndef INCLUDED_CHARLOTTE
#define INCLUDED_CHARLOTTE

#include "Character.h"
#include "SFML\Graphics.hpp"

class Charlotte: public Character
{
public:
	Charlotte(sf::Vector2f &position);
	~Charlotte();
	
	void update();
	void render();

	sf::Sprite getSprite();

};

#endif