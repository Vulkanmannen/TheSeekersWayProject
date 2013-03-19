#include "TutorialSign.h"
#include "ImageManager.h"
#include "Entity.h"
#include "ZoomedSign.h"
#include "EntityManager.h"


static const float WIDTH	= 40;
static const float HEIGHT	= 60;


TutorialSign::TutorialSign(sf::Vector2f &position, unsigned char spriteNumber)
{
	mPosition = position + sf::Vector2f(64, 64);
	mAlive = true;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = TUTORIALSIGN;	
	mLayer = MIDDLE;

	mZoomedSign = new ZoomedSign(mPosition, spriteNumber);
	EntityManager::getInstance()->addEntity(mZoomedSign);

	mTexture.loadFromImage(*ImageManager::getImage("TutorialSign.PNG"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);

	switch(spriteNumber)
	{
		case 0:
			mBaseSign = Entity::CHARACTER;
			break;

		case 1:
			mCharacterSign = Entity::KIBA;
			break;

		case 2:
			mCharacterSign = Entity::CHARLOTTE;
			break;

		case 3:
			mCharacterSign = Entity::CHARLOTTE;
			break;

		case 4:
			mBaseSign = Entity::CHARACTER;
			break;

		case 5:
			mCharacterSign = Entity::KIBA;
			break;

		case 6:
			mCharacterSign = Entity::CHARLOTTE;
			break;

		case 7:
			mCharacterSign = Entity::FENRIR;
			break;

		case 8:
			mBaseSign = Entity::CHARACTER;
			break;

		case 9:
			mCharacterSign = Entity::SHEEKA;
			break;

		case 10:
			mCharacterSign = Entity::SHEEKA;
			break;

		case 11:
			mCharacterSign = Entity::FENRIR;
			break;

		case 12:
			mCharacterSign = Entity::SHEEKA;
			break;

		case 13:
			mCharacterSign = Entity::FENRIR;
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
	if((*e) == CHARACTER && e->getEntityKind() == mCurrent && (mCharacterSign == mCurrent || mBaseSign == CHARACTER))
	{
		mZoomedSign->setCharacterOnSign(true);
	}
}

void TutorialSign::onSignFalse()
{
		mZoomedSign->setCharacterOnSign(false);
}