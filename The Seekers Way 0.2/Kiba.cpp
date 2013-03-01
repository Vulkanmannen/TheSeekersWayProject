#include "Kiba.h"
#include "Animation.h"
#include "ImageManager.h"
#include "Sounds.h"
#include <iostream>
const static float HEIGHT = 120;
const static float WIDTH = 56;

Kiba::Kiba(sf::Vector2f &position):
	telestate(free),
	mNoStone(sf::Vector2f(0,0)),
	mTeleBox(new TelekinesisBox(position, &mNoStone)),
	mCanPressQ(true),
	mCanPressChange(true)
{	
	mStone = 0;
	EntityManager::getInstance()->addEntity(mTeleBox);
	mAnimation.init("Kiba.png", 60, 6);
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = KIBA;
	mPosition = position + sf::Vector2f(0, 32);
}


Kiba::~Kiba()
	{}

void Kiba::update(EntityKind &currentEntity)
{
		
	move();
	
	if(mCanMove)
	{
		if(currentEntity == mEntityKind)
		{
			if(telestate == free)
			{
				walk();
				jump();
				slash();
			}


			teleStates();
		}
		else if(mStone != NULL)
		{
			if(mStone->mtelemove != false)
			{
				mStone->mtelemove = false;
			}
		}
	}
	
	Character::update(currentEntity);
	
	mTeleBox->setPosition(mPosition);
	//mTeleBox->stone.clear();
}


void Kiba::teleStates()
{
	if(telestate == choice)
	{
		
		mStone = mTeleBox->getStone();

		if(mTeleBox->getStoneVector().size() == 0)
		{
			telestate = free;
		}

		else if(mStone != NULL)
		{
			mStone->setStoneState(Stone::ONGROUND);
			mTeleBox->changeStone();
			mStone = mTeleBox->getStone();
			mStone->setStoneState(Stone::SELECTED);
		}	
		

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressQ || mTeleBox->getStoneVector().size() == 1)
		{
			mCanPressQ = false;

			if(mStone != NULL)
			{
				telestate = moving;			
				telekinesis();
			}
		}
	}

	else if(telestate == moving && mStone != NULL)
	{	
		mStone->mtelemove = true;

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressQ && mStone->onblock())
		{
			mCanPressQ = false;

			telestate = free;

			if(mStone != NULL)
			{
				mStone->mtelekinesis = false;
				mStone->setStoneState(Stone::ONGROUND);
			}
		}
	}

	else if(telestate == free)
	{
		mTeleBox->clearStoneVector();
		
		if(!mFalling && !mIsJumping)
		{
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressQ)
			{
				mCanPressQ = false;
				telestate = choice;
			}	
		}
	}


	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		mCanPressQ = true;
	}
}


void Kiba::render()
{
	sf::RenderStates states;
	if(mHurtShow)
		states.shader = &mHurtShader;
	mAnimation.update(mStatus * 2 + mDirLeft);

	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -68));
	ImageManager::render(&mAnimation.getSprite(), states);
}

void Kiba::telekinesis()
{
	if(mStone != NULL)
	{
		mStone->mtelekinesis = true;
		mStone->mtelemove = true;
		mStone->mKibaPos = mPosition;
		mStone->setStoneState(Stone::INTELE);

		mMovementSpeed.x = 0;
		mStatus = IDLE;
	}
}

void Kiba::getStone()
{

}

void Kiba::slash()
{ 
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mslashtimer.getElapsedTime().asSeconds() >= 1)
	{	
		mslashtimer.restart();
		Slash *slash = new Slash(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 32, mPosition.y - 30), mDirLeft);
		EntityManager::getInstance()->addEntity(slash);
		Sounds::getInstance()->Play("slash.wav");
	}
}
