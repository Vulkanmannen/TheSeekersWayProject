#ifndef INCLUDED_CHARLOTTE
#define INCLUDED_CHARLOTTE

#include "Character.h"
#include "SFML\Graphics.hpp"

class Charlotte: public Character
{
public:
	Charlotte(sf::Vector2f &position);
	~Charlotte();
	
	void update(EntityKind &currentEntity);
	void render();

	sf::Sprite getSprite();

private:

	sf::Clock mClock;

	void SetShield();

};

#endif