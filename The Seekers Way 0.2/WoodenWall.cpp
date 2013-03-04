#include "WoodenWall.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

WoodenWall::WoodenWall(sf::Vector2f &position, std::string &texture):
	mAnimation(texture, 30, 12, HEIGHT, WIDTH)
	{
		mPosition = position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = WOODENWALL;
	} 


WoodenWall::~WoodenWall()
	{}

void WoodenWall::update(EntityKind &currentCharacter)
{

}

void WoodenWall::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

// om en darkbinding åker in i switchen så öppnas dörren
void WoodenWall::interact(Entity *e)
{
	if(e->getEntityKind() == SLASH)
	{
		Activate();
	}
}

// öppnar dörren
void WoodenWall::Activate()
{
	destroy();
}