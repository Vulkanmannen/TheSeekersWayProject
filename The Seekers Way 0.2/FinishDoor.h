#ifndef INCLUDED_FINISHDOOR
#define INCLUDED_FINISHDOOR
#include "Object.h"
#include <SFML\Graphics.hpp>


class FinishDoor: public Object
{
public:
	FinishDoor(sf::Vector2f &position);
	~FinishDoor();

	void interact(Entity* e);
	void update(EntityKind &currentEntity);

private:

	sf::Clock mClock;

	void LoadNextLevel();
	void inGoalfalse();

	bool kibaInGoal;
	bool charlotteInGoal;
	bool fenrirInGoal;
	bool sheekaInGoal;
};

#endif