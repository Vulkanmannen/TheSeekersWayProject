#include "ZoomedSign.h"
#include "ImageManager.h"


static const float ZOOMEDWIDTH	= 400;
static const float ZOOMEDHEIGHT	= 282;

ZoomedSign::ZoomedSign(sf::Vector2f &position, unsigned char spriteNumber):
	mCharacterOnSign(false)
{
	mPosition = position + sf::Vector2f(0, -194);
	mAlive = true;
	mWidth = ZOOMEDWIDTH;
	mHeight = ZOOMEDHEIGHT;
	mEntityKind = ZOOMEDSIGN;
	mLayer = FORGROUND;

	mZoomedSignTexture.loadFromImage(*ImageManager::getImage("ZoomedTutorialSign.png"));
	mZoomedSignSprite.setTexture(mZoomedSignTexture);
	mZoomedSignSprite.setPosition(mPosition);
	mZoomedSignSprite.setOrigin(mZoomedSignSprite.getLocalBounds().width / 2, mZoomedSignSprite.getLocalBounds().height / 2);

	switch(spriteNumber)
	{
		case 0:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 1:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 2:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 3:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 4:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 5:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 6:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 7:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 8:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 9:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 10:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 11:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 12:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;

		case 13:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign.png"));
			break;
	}
}


ZoomedSign::~ZoomedSign()
{
}


void ZoomedSign::update(EntityKind &currentEntity)
{

}

void ZoomedSign::render()
{
 	if(mCharacterOnSign == true)
	{
		ImageManager::render(&mZoomedSignSprite);
	}
}

void ZoomedSign::setCharacterOnSign(bool CharacterOnSign)
{
	mCharacterOnSign = CharacterOnSign;
}