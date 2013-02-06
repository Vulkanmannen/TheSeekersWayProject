#include "FireBall.h"
#include "ImageManager.h"

static const float HEIGHT = 64;
static const float WIDTH = 64;

FireBall::FireBall(sf::Vector2f &position):
	mAnimation("FireBall.png", 60, 1, HEIGHT, WIDTH)
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

}

void FireBall::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}