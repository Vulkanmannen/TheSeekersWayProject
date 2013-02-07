#include "FireBall.h"
#include "ImageManager.h"
#include <cmath>

static const float HEIGHT = 64;
static const float WIDTH = 64;

FireBall::FireBall(sf::Vector2f &position):
	mAnimation("FireBall.png", 60, 4, HEIGHT, WIDTH),
	mCenterPos(position),
	mAngle(0),
	mRadius(64)
{
	mPosition = position + sf::Vector2f(-64, 0);
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = FIREBALL;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}


FireBall::~FireBall()
{
}

void FireBall::update(EntityKind &currentEntity)
{
	FireBallRot();
	updateAngle();
}

void FireBall::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void FireBall::updateAngle()
{
	mAngle += 3.14 * 0.02;
	if(mAngle >= 6.28)
	{
		mAngle = 0;
	}
}

void FireBall::FireBallRot()
{
	mNewpos.x = mCenterPos.x + std::sin(mAngle) * mRadius;
	mNewpos.y = mCenterPos.y + std::cos(mAngle) * mRadius;
	mPosition = mNewpos;
	//mAnimation.RotateAnimation(mAngle);
}