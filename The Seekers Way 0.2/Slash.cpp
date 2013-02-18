#include "Slash.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Slash::Slash(sf::Vector2f &position, bool mdirleft):
	mDirLeft(mdirleft),
	mAnimation("SLASH.png", 60, 5, 128, WIDTH)
	{
		mPosition = position;
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = SLASH;
	}


Slash::~Slash()
	{}

void Slash::update(EntityKind &currentCharacter)
{
	//mPosition += sf::Vector2f((mDirLeft? -1: 1) * 10, 0 );
	if(mAnimation.getEndOfAnimation())
	{
		destroy();
	}
}

void Slash::render()
{
	mAnimation.update(mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

// om en darkbinding åker in i switchen så öppnas dörren
void Slash::interact(Entity *e)
{

}