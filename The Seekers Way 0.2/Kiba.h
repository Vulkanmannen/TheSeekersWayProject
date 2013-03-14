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

	void update(EntityKind &currentEntity);
	void render();

	void onblock();
	
private:
	void slash();
	sf::Clock mslashtimer;

	TelekinesisBox* mTelekinesisBox;

	enum TeleState {NOSTONE, CHOOSING, SELECTEDSTONE};
	TeleState mTeleState;

	Stone* mStone;
	bool mCanPressStone;

	void noStone();
	void choosing();
	void selectedStone();
};

#endif