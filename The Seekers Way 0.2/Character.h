#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "SFML\Graphics.hpp"
#include "Entity.h"

class Character: public Entity
{
public:
	Character();
	~Character();

	sf::Vector2f position();

private:

	bool mJumping;
	bool mFalling;

	sf::Vector2f mMove();
	sf::Vector2f mJump();
};

#endif
