#ifndef INCLUDED_FIREBALL
#define INCLUDED_FIREBALL
#include "Object.h"
#include "Animation.h"

class FireBall: public Object
{
public:
	FireBall(sf::Vector2f &position);
	~FireBall();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

protected:

	Animation mAnimation;

	sf::Sprite mSprite;

	void FireBallRot();
	void updateAngle();

	sf::Vector2f mCenterPos;
	sf::Vector2f mNewpos;

	float mRadius;
	float mAngle;
};

#endif