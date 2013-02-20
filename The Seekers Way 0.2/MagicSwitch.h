#ifndef INCLUDED_MAGICSWITCH
#define INCLUDED_MAGICSWITCH

#include "Animation.h"
#include "Object.h"
#include "Block.h"

class MagicSwitch : public Object
{
public:
	MagicSwitch(sf::Vector2f &position, Block* door, float timeOpen);
	~MagicSwitch();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

	void Activate();
	void DisActivate();
private:
	Animation mAnimation;

	bool mIsPressed;
	Block* mBlock;
	float mTimeOpen;
	bool mOpen;

	sf::Clock mClockOpen;
};

#endif