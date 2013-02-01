#ifndef INCLUDED_SHIELD
#define INCLUDED_SHIELD
#include "Animation.h"
#include "Object.h"


class Shield: public Object
{
public:
	Shield(sf::Vector2f &position, bool dirLeft);

	~Shield();

	void render();
	void update(EntityKind &currentEntity);

	int ShieldCount;
	void ShieldLife();
	void interact(Entity* e);

private:
	Animation mAnimation;
	bool mDirLeft;
};

#endif