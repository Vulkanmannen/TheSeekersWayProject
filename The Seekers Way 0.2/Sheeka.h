#ifndef INCLUDED_SHEEKA
#define INCLUDED_SHEEKA

#include "SFML\System.hpp"
#include "Character.h"
#include "SFML\Graphics.hpp"

class Sheeka: public Character
{
public:
	Sheeka(sf::Vector2f &position);
	~Sheeka();
		
	void update(EntityKind &currentEntity);
	void render();

	sf::Sprite getSprite();

private:
	sf::Clock mDarkBindingClock;
	int mCanDashCount;
	int mCanDashTime;

	void SheekaDash();
	void dashTime();
	void notDashing();
	void darkBinding();

	void takeDamage();
	
	int mDashCount;
	int mDashTimer;
	float mDashAcc;

	bool mDash;
	bool mDashPressed;

	bool mCanPressDarkBinding;
};

#endif
