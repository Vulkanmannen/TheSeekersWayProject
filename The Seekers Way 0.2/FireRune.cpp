#include "FireRune.h"
#include "FireBall.h"
#include "ImageManager.h"
#include "EntityManager.h"

static const float HEIGHT = 64;
static const float WIDTH = 64;

FireRune::FireRune(sf::Vector2f &position):
	mAnimation("FireRune.png", 60, 1, HEIGHT, WIDTH),
	mFireTrapStatus(IDLE)
{
	mPosition = position + sf::Vector2f(0,32);
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = FIREBALL;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}

FireRune::~FireRune()
{
}

void FireRune::update(EntityKind &currentEntity)
{
	FireBallCircle();
}

void FireRune::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void FireRune::FireBallCircle()
{
	if(mClock.getElapsedTime().asSeconds() >= 0 && mClock.getElapsedTime().asSeconds() < 1)
	{
		EntityManager::getInstance()->addEntity(new FireBall(mPosition));
	}
}