#ifndef INCLUDED_CHARACTER
#define INCLUDED_CHARACTER

#include "SFML\Graphics.hpp"
#include "Entity.h"

class Character: public Entity
{
public:
	Character(sf::Vector2f &getPosition);
	~Character();
	void update();
private:

	enum Status
	{
		IDLE,
		JUMP,
		JUMPING,
		FALL,
		LANDING,
		ACTION1,
		ACTION2,
		WALK
	};

	enum Direction
	{
		LEFT,
		RIGHT
	};
	sf::Vector2f mMovementSpeed;
	sf::Vector2f mDirection;
	sf::Vector2f mPosition;

	void move();
	void jump();
	void fall();
	void walk();
	void jumping();
	void falling();

	bool mAlive;
	float mAcceleration;
	float mDecrease;
	float mGravity;

};

#endif
