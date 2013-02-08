#ifndef INCLUDED_CHARLOTTE
#define INCLUDED_CHARLOTTE

#include "Character.h"
#include "SFML\Graphics.hpp"
#include "Shield.h"
class Charlotte: public Character
{
public:
	Charlotte(sf::Vector2f &position);
	~Charlotte();
	
	void update(EntityKind &currentEntity);
	void render();

	sf::Sprite getSprite();

private:
	
	Shield* mShield;
	sf::Clock mClock;

	void SetShield();
	void GetShieldLife();
	bool mIsShield;
};

#endif