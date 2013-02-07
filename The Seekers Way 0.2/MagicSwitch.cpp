#include "MagicSwitch.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

MagicSwitch::MagicSwitch(sf::Vector2f &position, Block* door, float timeOpen):
	mIsPressed(false),
	mAnimation("magicswitch.png", 60, 1, HEIGHT, WIDTH),
	mTimeOpen(timeOpen),
	mBlock(door)
	{
		mPosition = position;
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = BUTTON;
	}


MagicSwitch::~MagicSwitch()
	{}

void MagicSwitch::update(EntityKind &currentCharacter)
{
	DisActivate();
}

void MagicSwitch::render()
{
	mAnimation.update(mIsPressed);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

// om en darkbinding åker in i switchen så öppnas dörren
void MagicSwitch::interact(Entity *e)
{
	if(e->getEntityKind() == DARKBINDING)
	{
		Activate();
	}
}

// öppnar dörren
void MagicSwitch::Activate()
{
	if(mIsPressed == false)
	{
		mBlock->Activate();
		mClockOpen.restart();
	}
	mIsPressed = true;
}

// stänger dörren
void MagicSwitch::DisActivate()
{
	if(mIsPressed == false && mClockOpen.getElapsedTime().asSeconds() > mTimeOpen)
	{
		mBlock->DisActivate();
	}
	mIsPressed = false;
}