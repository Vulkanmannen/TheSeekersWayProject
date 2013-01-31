#ifndef INCLUDED_SHIELD
#define INCLUDED_SHIELD
#include "Animation.h"

class Shield
{
public:
	Shield(sf::Vector2f &position);

	~Shield();

	void render();
	void update();

	sf::Sprite getSprite();

private:
	Animation mAnimation;
};

#endif