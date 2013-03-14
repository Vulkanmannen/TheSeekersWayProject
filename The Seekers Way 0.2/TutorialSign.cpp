#include "TutorialSign.h"
#include "ImageManager.h"
#include "Entity.h"
#include "ZoomedSign.h"
#include "EntityManager.h"


static const float WIDTH	= 40;
static const float HEIGHT	= 64;


TutorialSign::TutorialSign(sf::Vector2f &position)
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