#include "ZoomedSign.h"
#include "ImageManager.h"


static const float ZOOMEDWIDTH	= 400;
static const float ZOOMEDHEIGHT	= 282;

ZoomedSign::ZoomedSign(sf::Vector2f &position):
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