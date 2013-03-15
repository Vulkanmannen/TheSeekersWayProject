#ifndef INCLUDED_CHARLOTTE
#define INCLUDED_CHARLOTTE

#include "Character.h"
#include "SFML\Graphics.hpp"
#include "Shield.h"
#include "Portal.h"

class Charlotte: public Character
{
public:
	Charlotte(sf::Vector2f &position);
	~Charlotte();
	
	void update(EntityKind &currentEntity);
	void render();
	void interact(Entity* e);

	sf::Sprite getSprite();

private:
	
	Shield* mShield;
	sf::Clock mClock;

	void SetShield();
	void GetShieldLife();
	void shieldTime();
	bool mActivatingShield;
	bool mIsShield;
	sf::Clock mShieldClock;

	bool mActiveCharacter;

	bool mTeleporting;
	bool mPlayCantTeleport;
	bool mCanPressTeleport;
	void teleporting();

	sf::Clock mTeleportClock;
	float mTimeToTeleport;
	Portal* mPortal;
};

#endif