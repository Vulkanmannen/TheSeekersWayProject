#include "PauseMenu.h"
#include "ImageManager.h"
#include "State.h"


PauseMenu::PauseMenu()
{
	mPauseText.loadFromFile("PauseMenu.PNG");
	mPauseSprite.setTexture(mPauseText);
	generateButtons();
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{
	updateCurrentButton();
	changeButton();
	buttonActivate();
}

void PauseMenu::render()
{
	mPauseSprite.setPosition(0, 0);
	ImageManager::render(&mPauseSprite);
	renderButtons();
}

void PauseMenu::generateButtons()
{
	for(int i = 0; i < 2; ++i)
	{
		Animation animation("KNAPP.PNG", 80, 1, 46, 123);
		animation.setPosition(sf::Vector2f(450, 200 + i*70));
		mButtons.push_back(animation);
	}
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
		switch(currentButton)
		{
			case 0:
				State::getInstance()->setState(State::GameState);
				break;

			case 1:
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