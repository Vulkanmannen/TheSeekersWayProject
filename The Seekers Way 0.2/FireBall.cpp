#include "FireBall.h"
#include "ImageManager.h"
#include <cmath>

static const float HEIGHT = 30;
static const float WIDTH = 30;

static const float SPRITEHEIGHT = 64;
static const float SPRITEWIDTH = 64;

FireBall::FireBall(sf::Vector2f &position):
	mAnimation("FireBall.png", 60, 4, SPRITEHEIGHT, SPRITEWIDTH),
	mCenterPos(position),
	mAngle(0),
	mRadius(64)
{
	mPosition = position + sf::Vector2f(-64, 0);
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = FIREBALL;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH/ 2, mPosition.y - SPRITEHEIGHT/ 2));
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
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH/ 2, mPosition.y - SPRITEHEIGHT/ 2));
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

void FireBall::interact(Entity* e)
{
	//
	//if(e->getEntityKind() == SPIKETRAP || e->getEntityKind() == FIREBALL)
	//{
	//	if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
	//	{
	//		if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
	//		{
	//			mPosition = sf::Vector2f(e->getPosition().x + xRadius - 3, mPosition.y);
	//		}
	//	}
	//}
}