#include "FireRune.h"
#include "FireBall.h"
#include "ImageManager.h"
#include "EntityManager.h"

static const float HEIGHT = 64;
static const float WIDTH = 64;

FireRune::FireRune(sf::Vector2f &position):
	mAnimation("FireRune.png", 90, 7, HEIGHT, WIDTH)
{
	mPosition = position;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = FIRERUNE;
	mAlive = true;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	EntityManager::getInstance()->addEntity(new FireBall(mPosition));
}

FireRune::~FireRune()
	{}

void FireRune::update(EntityKind &currentEntity)
{
	
}

void FireRune::render()
{
	mAnimation.update(0);
	ImageManager::render(&mAnimation.getSprite());
}