#include "DialogState.h"
#include "Dialogue.h"
#include "State.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "ImageManager.h"

DialogState::DialogState():
mPlayMovie(false),
mTimeToMovie(0)
{
	mTexture.loadFromImage(*ImageManager::getImage("black.png"));
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}


DialogState::~DialogState()
{
}

void DialogState::render()
{
	Dialogue::getInstance()->render();

	if(mPlayMovie)
	{
		int timeTemp = 5 + mTimeToMovie * 5;

		if(timeTemp > 255)
		{
			timeTemp = 255;
		}

		mSprite.setColor(sf::Color(0, 0, 0, timeTemp));
		mSprite.setPosition(EntityManager::getInstance()->getView()->getCenter());
		ImageManager::render(&mSprite);
	}
}

void DialogState::update()
{
	Dialogue::getInstance()->update();
	EntityManager::getInstance()->updateView();
	if(Dialogue::getInstance()->getendofDialogue() && Dialogue::getInstance()->getStartDialogue())
	{
			State::getInstance()->setState(State::GameState);
	}
	else if(Dialogue::getInstance()->getendofDialogue() && !Dialogue::getInstance()->getStartDialogue())
	{
		mPlayMovie = true;
	}

	if(mPlayMovie)
	{
		mTimeToMovie += 1;
		if(mTimeToMovie > 50)
		{
			LevelManager::getInstance()->LoadLevel(LevelManager::getInstance()->getCurrentLevel() + 1);
			State::getInstance()->setState(State::MyVideoState);
			mPlayMovie = false;
			mTimeToMovie = 0;
		}
	}
}