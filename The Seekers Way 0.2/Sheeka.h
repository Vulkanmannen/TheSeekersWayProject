#ifndef INCLUDED_SHEEKA
#define INCLUDED_SHEEKA

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
	Animation mAnimation;

protected:

	void	SheekaDash();
	float	mDash;

};

#endif
