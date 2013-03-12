#include "TutorialSign.h"
#include "ImageManager.h"
#include "Entity.h"

static const float WIDTH	= 64;
static const float HEIGHT	= 64;

static const float ZOOMEDWIDTH	= 800;
static const float ZOOMEDHEIGHT	= 563;


TutorialSign::TutorialSign(sf::Vector2f &position):
	kibaOnSign(false),
	charlotteOnSign(false),
	fenrirOnSign(false),
	sheekaOnSign(false)
{
	mPosition = position + sf::Vector2f(64, 64);
	mAlive = true;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = TUTORIALSIGN;
	mLayer = MIDDLE;

	mTexture.loadFromImage(*ImageManager::getImage("TutorialSign.PNG"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);

	mZoomedSignTexture.loadFromImage(*ImageManager::getImage("ZoomedTutorialSign.png"));
	mZoomedSignSprite.setTexture(mZoomedSignTexture);
	mZoomedSignSprite.setPosition(mPosition + sf::Vector2f(0, -194));
	mZoomedSignSprite.setOrigin(mZoomedSignSprite.getLocalBounds().width / 2, mZoomedSignSprite.getLocalBounds().height / 2);
}


TutorialSign::~TutorialSign()
{
}

void TutorialSign::update(EntityKind &currentEntity)
{
	onSignFalse();
}

void TutorialSign::render()
{
	if(kibaOnSign == true)
	{
		ImageManager::render(&mZoomedSignSprite);
	}
	if(charlotteOnSign == true)
	{
		ImageManager::render(&mZoomedSignSprite);
	}

	ImageManager::render(&mSprite);
}

void TutorialSign::interact(Entity* e)
{
	if((*e) == KIBA)
	{
		kibaOnSign = true;
	}
	else if((*e) == CHARLOTTE)
	{
		charlotteOnSign = true;
	}
	else if((*e) == FENRIR)
	{
		fenrirOnSign = true;
	}
	else if((*e) == SHEEKA)
	{
		sheekaOnSign = true;
	}
}

void TutorialSign::onSignFalse()
{
	if(mClock.getElapsedTime().asMilliseconds() >= 100)
	{
		kibaOnSign		= false;
		charlotteOnSign	= false;
		fenrirOnSign	= false;
		sheekaOnSign	= false;
		mClock.restart();
	}
}