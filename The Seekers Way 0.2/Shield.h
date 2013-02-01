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
	void update(EntityKind &currentEntity);
	 int GetShieldCount()const;
	void interact(Entity* e);

private:
	Animation mAnimation;
	int mShieldCount;
};

#endif