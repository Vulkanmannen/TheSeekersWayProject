#ifndef	INCLUDED_TUTORIALSIGN
#define INCLUDED_TUTORIALSIGN

#include "Object.h"

class ZoomedSign;

class TutorialSign: public Object
{
public:
	TutorialSign(sf::Vector2f &position, unsigned char spriteNumber);
	~TutorialSign();

	void update(EntityKind &currentEntity);
	void render();
	void interact(Entity* e);

private:

	sf::Clock mClock;

	void onSignFalse();

	EntityKind mCurrent;
	EntityKind mCharacterSign;
	BaseKind mBaseSign;

	ZoomedSign *mZoomedSign;
};

#endif