#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "SFML\Graphics.hpp"
#include "Entity.h"

class Character: public Entity
{
public:
	Character();
	~Character();
	void update();
	

private:

	sf::Vector2f mMovementSpeed;
	sf::Vector2f mDirection;
	sf::Vector2f mPosition;
	
	bool mJumping();
	bool mFalling();
	bool mAlive();

	void move();
	void jump();
	void fall();
	void walk();
	void jumping();
	void falling();

	float mAcceleration();

};

#endif
