#include "FinishDoor.h"
#include "ImageManager.h"
#include "Entity.h"
#include "LevelManager.h"
#include "EntityManager.h"
#include "State.h"
#include "Dialogue.h"


static const float WIDTH = 192;
static const float HEIGHT = 192;

FinishDoor::FinishDoor(sf::Vector2f &position):
	kibaInGoal(false),
	charlotteInGoal(false),
	fenrirInGoal(false),
	sheekaInGoal(false),
	mAllInGoal(false),
	mNumberOfCharactersInGoal(0)
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
	updateCharactersInGoal();
	if(mNumberOfCharactersInGoal >= EntityManager::getInstance()->getSizeOfCharacterVector())
	{
		if(mAllInGoal == false)
		{
			mClockAllIn.restart();
		}
		mAllInGoal = true;
	}
	else
	{
		mAllInGoal = false;
	}
	if(mClockAllIn.getElapsedTime().asSeconds() > 2 && mAllInGoal)
	{
		EntityManager::getInstance()->SetAniToIdle();
		LevelManager::getInstance()->LoadEndLevel();
		Dialogue::getInstance()->setStartDialogue(false);
		State::getInstance()->setState(State::DialogueState);
	}
}

void FinishDoor::updateCharactersInGoal()
{
	mNumberOfCharactersInGoal = 0;
	if(kibaInGoal)
	{
		mNumberOfCharactersInGoal++;
	}
	if(charlotteInGoal)
	{
		mNumberOfCharactersInGoal++;
	}
	if(fenrirInGoal)
	{
		mNumberOfCharactersInGoal++;
	}
	if(sheekaInGoal)
	{
		mNumberOfCharactersInGoal++;
	}
}

void FinishDoor::inGoalfalse()
{
		sheekaInGoal = false;
		fenrirInGoal = false;
		charlotteInGoal = false;
		kibaInGoal = false;
}