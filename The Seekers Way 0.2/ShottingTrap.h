#ifndef INCLUDED_ShottingTrap
#define INCLUDED_ShottingTrap

#include "Object.h"
#include "Animation.h"
#include "EntityManager.h"
#include "Arrow.h"

class ShottingTrap: public Object
{
public:
	ShottingTrap(sf::Vector2f &position, int time, bool shot = true, bool dirleft = true);
	~ShottingTrap();

	void update(EntityKind &currentEntity);
	void render();

	void Activate();
	void DisActivate();

private:
	Animation mAnimation;

	sf::Clock mShottingTimer;

	bool mDirLeft;
	bool mShotting;

	int mTimeToShot;
};

#endif