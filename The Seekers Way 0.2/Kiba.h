#ifndef INCLUDED_KIBA
#define INCLUDED_KIBA

#include "Character.h"
#include "SFML\Graphics.hpp"
#include "TeleKinesisBox.h"
#include "EntityManager.h"
#include "Slash.h"
#include "Stone.h"


class Kiba: public Character
{
public:
	Kiba(sf::Vector2f &position);
	~Kiba();

	enum tele {choice, moving, free};
	tele telestate;

	void telekinesis();
	void update(EntityKind &currentEntity);
	void render();
	void getStone();
	void slash();

private:
	void teleStates();

	bool mCanPressQ;
	bool mCanPressChange;

	Stone *mStone;
	Stone mNoStone;

	TelekinesisBox *mTeleBox;
	//sf::Clock teletimer;
	sf::Clock mslashtimer;
};

#endif