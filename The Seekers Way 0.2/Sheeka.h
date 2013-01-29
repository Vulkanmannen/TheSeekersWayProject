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
		
	void update();
	void render();

	sf::Sprite getSprite();

private:
<<<<<<< HEAD
	Animation mAnimation;

=======
>>>>>>> origin/master
	sf::Clock mClock;

	void SheekaDash();
	
	int mDashCount;
	int mDashTimer;
	float mDashAcc;
	float mMaxDashDist;

	bool mDash;
	bool mDashPressed;
};

#endif
