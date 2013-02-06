#ifndef INCLUDED_MAGICSWITCH
#define INCLUDED_MAGICSWITCH

#include "Animation.h"
#include "Block.h"

class MagicSwitch : public Block
{
public:
	MagicSwitch(sf::Vector2f &position, float timeOpen);
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

	sf::Clock mClockOpen;
};

#endif