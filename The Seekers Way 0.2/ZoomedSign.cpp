#include "ZoomedSign.h"
#include "ImageManager.h"
#include "Entity.h"


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
			
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign1.png"));
			break;

		case 1:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign2.png"));
			break;

		case 2:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign3.png"));
			break;

		case 3:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign4.png"));
			break;

		case 4:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign5.png"));
			break;

		case 5:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign6.png"));
			break;

		case 6:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign7.png"));
			break;

		case 7:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign8.png"));
			break;

		case 8:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign9.png"));
			break;

		case 9:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign10.png"));
			break;

		case 10:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign11.png"));
			break;

		case 11:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign12.png"));
			break;

		case 12:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign13.png"));
			break;

		case 13:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign14.png"));
			break;

		case 14:
			mZoomedSignTexture.loadFromImage(*ImageManager::getImage("Sign15.png"));
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