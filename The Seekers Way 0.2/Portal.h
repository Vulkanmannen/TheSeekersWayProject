#ifndef INCLUDED_Portal
#define INCLUDED_Portal

#include "Object.h"
#include "SFML\Graphics.hpp"
#include "EntityManager.h"
#include "Animation.h"


class Portal : public Object
{
public:
	Portal(sf::Vector2f position1, sf::Vector2f position2);
	~Portal();
	void interact(Entity* e);
	void update(EntityKind &currentEntity);
	void render();
	sf::Vector2f getDestination();

private:	
	Animation mAnimation;
	Portal(sf::Vector2f position, Portal *p);
	Portal *mPortal;
};

#endif