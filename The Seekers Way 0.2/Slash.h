#ifndef INCLUDED_Slash
#define INCLUDED_Slash

#include "Animation.h"
#include "Object.h"

class Slash : public Object
{
public:
	Slash(sf::Vector2f &position, bool mdirleft);
	~Slash();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

private:
	Animation mAnimation;
	bool mDirLeft;
	sf::Clock mSlashTime;
};

#endif