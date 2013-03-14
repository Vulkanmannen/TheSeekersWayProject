#include "TutorialSign.h"
#include "ImageManager.h"
#include "Entity.h"
#include "ZoomedSign.h"
#include "EntityManager.h"


static const float WIDTH	= 40;
static const float HEIGHT	= 64;


TutorialSign::TutorialSign(sf::Vector2f &position, unsigned char spriteNumber)
{
	mPosition = position + sf::Vector2f(64, 64);
	mAlive = true;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = TUTORIALSIGN;	
	mLayer = MIDDLE;

	mZoomedSign = new ZoomedSign(mPosition, 11);
	EntityManager::getInstance()->addEntity(mZoomedSign);

	mTexture.loadFromImage(*ImageManager::getImage("TutorialSign.PNG"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);

	switch(spriteNumber)
	{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		case 9:
			break;

		case 10:
			break;

		case 11:
			break;

		case 12:
			break;
	}
}

TutorialSign::~TutorialSign()
{
	
}

void TutorialSign::update(EntityKind &currentEntity)
{
	mCurrent = currentEntity;
	onSignFalse();
}

void TutorialSign::render()
{
	ImageManager::render(&mSprite);
}

void TutorialSign::interact(Entity* e)
{
	if((*e) == CHARACTER && e->getEntityKind() == mCurrent)
	{
		mZoomedSign->setCharacterOnSign(true);
	}
}

void TutorialSign::onSignFalse()
{
		mZoomedSign->setCharacterOnSign(false);
}