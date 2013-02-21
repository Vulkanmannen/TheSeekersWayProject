#include "FinishDoor.h"
#include "ImageManager.h"
#include "Entity.h"
#include "LevelManager.h"


static const float WIDTH = 192;
static const float HEIGHT = 192;

FinishDoor::FinishDoor(sf::Vector2f &position):
	kibaInGoal(false),
	charlotteInGoal(false),
	fenrirInGoal(false),
	sheekaInGoal(false),
	mAllInGoal(false)
{
	mPosition = position + sf::Vector2f(64, 64);
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = FINISHDOOR;
	mLayer = BACKGROUND;

	mTexture.loadFromImage(*ImageManager::getImage("FinishDoor.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}


FinishDoor::~FinishDoor()
{
}

void FinishDoor::update(EntityKind &currentEntity)
{
	LoadNextLevel();
	inGoalfalse();
}

void FinishDoor::interact(Entity* e)
{
	if((*e) == KIBA)
	{
		kibaInGoal = true;
	}

	if((*e) == CHARLOTTE)
	{
		charlotteInGoal = true;
	}

	if((*e) == FENRIR)
	{
		fenrirInGoal = true;
	}

	if((*e) == SHEEKA)
	{
		sheekaInGoal = true;
	}
}

void FinishDoor::LoadNextLevel()
{
	if(kibaInGoal == true && charlotteInGoal == true && fenrirInGoal == true && sheekaInGoal == true)
	{
		if(mAllInGoal == false)
		{
			mClockAllIn.restart();
		}
		mAllInGoal = true;
	}

	if(mClockAllIn.getElapsedTime().asSeconds() > 2 && mAllInGoal)
	{
		LevelManager::getInstance()->LoadLevel(LevelManager::getInstance()->getCurrentLevel() + 1);
	}
}

void FinishDoor::inGoalfalse()
{
	if(mClock.getElapsedTime().asSeconds() >= 3)
	{
		sheekaInGoal = false;
		fenrirInGoal = false;
		charlotteInGoal = false;
		kibaInGoal = false;
		mClock.restart();
	}
}