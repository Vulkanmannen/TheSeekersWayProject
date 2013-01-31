#ifndef INCLUDED_ShottingTrap
#define INCLUDED_ShottingTrap
#include "Animation.h"
#include "Block.h"
#include "EntityManager.h"
#include "Arrow.h"

class ShottingTrap: public Block
{
public:
	ShottingTrap(sf::Vector2f &position, bool shot = true, bool dirleft = true);
	~ShottingTrap();

	void update(EntityKind &currentEntity);

	void Activate();
	void DisActivate();

private:
	sf::Clock mShottingTimer;

	bool mDirLeft;
	bool mShotting;
};

#endif