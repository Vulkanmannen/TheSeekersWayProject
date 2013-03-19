#include "PauseMenu.h"
#include "ImageManager.h"
#include "State.h"
#include "EntityManager.h"
#include "LevelManager.h"


PauseMenu::PauseMenu():
	HowToPlay(false),
	canPressJournal(true),
	currentButton(0),
	currentJournalFrame(0)
{
	mPauseText.loadFromImage(*ImageManager::getImage("Howtoplayinst.PNG"));
	mHowToPlayKiba.loadFromImage(*ImageManager::getImage("journal_Kiba.png"));
	mHowToPlayCharlotte.loadFromImage(*ImageManager::getImage("journal_Charlotte.png"));
	mHowToPlayFenrir.loadFromImage(*ImageManager::getImage("journal_Fenrir.png"));
	mHowToPlaySheeka.loadFromImage(*ImageManager::getImage("journal_Sheeka.png"));
	mMapTexture.loadFromImage(*ImageManager::getImage("journalMap.png"));

	mPauseSprite.setTexture(mPauseText);
	mHowToPlaySpriteSheeka.setTexture(mHowToPlaySheeka);
	mHowToPlaySpriteFenrir.setTexture(mHowToPlayFenrir);
	mHowToPlaySpriteCharlotte.setTexture(mHowToPlayCharlotte);
	mHowToPlaySpriteKiba.setTexture(mHowToPlayKiba);
	mMapSprite.setTexture(mMapTexture);

	mPauseSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteKiba.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteCharlotte.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteFenrir.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteSheeka.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mMapSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	
	mSpriteVector.push_back(&mHowToPlaySpriteKiba);
	mSpriteVector.push_back(&mHowToPlaySpriteCharlotte);
	mSpriteVector.push_back(&mHowToPlaySpriteFenrir);
	mSpriteVector.push_back(&mHowToPlaySpriteSheeka);
	mSpriteVector.push_back(&mMapSprite);

	generateButtons();
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{
	if(HowToPlay == false)
	{
		updateCurrentButton();
		changeButton();
	}
	else 
	{
		changeJournalFrame();
	}

	updateButtons();
	buttonActivate();

}

void PauseMenu::render()
{
	EntityManager::getInstance()->render();
	ImageManager::render(&mPauseSprite);
	updateButtons();
	renderButtons();
	if(HowToPlay == true)
	{
		ImageManager::render(mSpriteVector[currentJournalFrame]);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			HowToPlay = false;
			State::getInstance()->setmEsc(false);
		}
	}

	mPauseSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteKiba.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteCharlotte.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteFenrir.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mHowToPlaySpriteSheeka.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
	mMapSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));

}

void PauseMenu::generateButtons()
{
		Animation animation("Resume.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation);

		Animation animation2("RestartLevel.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation2);

		Animation animation3("HowToPlay.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation3);

		//Animation animation4("Audio.png", 80, 1, 64, 192);
		//updateButtons();
		//mButtons.push_back(animation4);
		
		Animation animation5("MainMenu.PNG", 80, 1,64 , 192);
		updateButtons();
		mButtons.push_back(animation5);
}

void PauseMenu::updateButtons()
{
	for(std::vector<Animation>::size_type i = 0; i < mButtons.size(); i++)
	{
		mButtons[i].setPosition(mPauseSprite.getPosition() + sf::Vector2f(120, 120 + i*70));
	}
}

void PauseMenu::changeButton()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && canPressMenu)
	{
		currentButton++;
		canPressMenu = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canPressMenu)
	{
		currentButton--;
		canPressMenu = false;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		canPressMenu = true;	
	}


	if(currentButton >= static_cast<int>(mButtons.size()))
	{
		currentButton = 0;
	}
	else if(currentButton < 0)
	{
		currentButton = static_cast<int>(mButtons.size()) -1;
	}
}

void PauseMenu::renderButtons()
{
	for(auto i = mButtons.begin(); i != mButtons.end(); i++)
	{
		ImageManager::render(&i->getSprite());
	}
}

void PauseMenu::updateCurrentButton()
{
	for(std::vector<Animation>::size_type i = 0; i < mButtons.size(); i++)
	{
		mButtons[i].update(i == currentButton);
	}
}

void PauseMenu::buttonActivate()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canPressReturn)
	{
		canPressReturn = false;
		switch(currentButton)
		{
			case 0:
				State::getInstance()->setState(State::GameState);
				break;

			case 1:
				LevelManager::getInstance()->LoadLevel();
				State::getInstance()->setState(State::GameState);
				break;

			case 2:
				HowToPlay = !HowToPlay;
				break;

			//case 3:
			//	break;

			case 3:
				State::getInstance()->setState(State::StartState);
				break;
		}
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		canPressReturn = true;
	}
}

int PauseMenu::setCurrentButton()
{
	return currentButton = 0;
}

void PauseMenu::SetCanPressToFalse()
{
	canPressReturn = false;
}

bool PauseMenu::HowToPlayInst()
{
	return HowToPlay;
}

void PauseMenu::changeJournalFrame()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && canPressJournal)
	{
		currentJournalFrame--;
		canPressJournal = false;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && canPressJournal)
	{
		currentJournalFrame++;
		canPressJournal = false;
	}

	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		canPressJournal = true;
	}

	if(currentJournalFrame < 0)
	{
		currentJournalFrame = 4;
	}

	else if(currentJournalFrame > 4)
	{
		currentJournalFrame = 0;
	}
}