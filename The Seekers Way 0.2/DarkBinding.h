#ifndef INCLUDED_DARKBINDING
#define INCLUDED_DARKBINDING

#include "Object.h"
//#include "SFML\Graphics.hpp"
#include "Animation.h"

class DarkBinding : public Object
{
public:
	DarkBinding(sf::Vector2f &position, bool dirLeft);
	~DarkBinding();

	void update(EntityKind &currentEntity);
	void render();

	void interact(Entity* e);
private:
	Animation mAnimation;

	void move();

	float mMovementSpeed;
	bool mDirLeft;
};

#endif