#include "PauseMenu.h"
#include "ImageManager.h"
#include "State.h"
#include "EntityManager.h"


PauseMenu::PauseMenu():
	HowToPlay(false)
{
	mPauseText.loadFromFile("journal.PNG");
	mPauseSprite.setTexture(mPauseText);
	mHowToPlay.loadFromFile("Howtoplayinst.png");
	mHowToPlaySprite.setTexture(mHowToPlay);
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
	buttonActivate();
}

void PauseMenu::render()
{
	EntityManager::getInstance()->render();
	mPauseSprite.setPosition(100, 60);
	ImageManager::render(&mPauseSprite);
	renderButtons();
	if(HowToPlay == true)
	{
		mHowToPlaySprite.setPosition(0, 0);
		ImageManager::render(&mHowToPlaySprite);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			HowToPlay = false;
			State::getInstance()->setmEsc(false);
		}
	}
}

void PauseMenu::generateButtons()
{
		Animation animation("Resume.PNG", 80, 1, 46, 123);
		animation.setPosition(sf::Vector2f(230, 100 + 1*70));
		mButtons.push_back(animation);

		Animation animation3("HowToPlay.PNG", 80, 1, 46, 123);
		animation3.setPosition(sf::Vector2f(230, 100 + 2*70));
		mButtons.push_back(animation3);

		Animation animation4("MainMenu.PNG", 80, 1, 46, 123);
		animation4.setPosition(sf::Vector2f(230, 100 + 3*70));
		mButtons.push_back(animation4);
}

void PauseMenu::changeButton()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && canPress)
	{
		currentButton++;
		canPress = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canPress)
	{
		currentButton--;
		canPress = false;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		canPress = true;	
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
				HowToPlay = !HowToPlay;
				break;

			case 2:
				State::getInstance()->setState(State::StartState);
				break;
		}
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		canPressReturn = true;
	}
}

void PauseMenu::SetCanPressToFalse()
{
	canPressReturn = false;
}

bool PauseMenu::HowToPlayInst()
{
	return HowToPlay;
}