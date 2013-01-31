#ifndef INCLUDED_Object
#define INCLUDED_Object

#include "Entity.h"
#include "SFML\Graphics.hpp"



class Object: public Entity
{
public:
	Object();
	virtual ~Object();
	virtual void interact(Entity* e);
};

#endif