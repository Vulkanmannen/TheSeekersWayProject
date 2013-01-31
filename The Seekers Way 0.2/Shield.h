#ifndef INCLUDED_SHIELD
#define INCLUDED_SHIELD
#include "Animation.h"
#include "Object.h"


class Shield: public Object
{
public:
	Shield(sf::Vector2f &position);

	~Shield();

	void render();
	void update();

private:
	Animation mAnimation;
};

#endif