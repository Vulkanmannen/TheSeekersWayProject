#include "Kiba.h"
#include "Animation.h"
#include "ImageManager.h"
#include "Sounds.h"
#include <iostream>

const static float HEIGHT = 120;
const static float WIDTH = 56;

Kiba::Kiba(sf::Vector2f &position):
	mTelekinesisBox(new TelekinesisBox(position)),
	mTeleState(NOSTONE),
	mStone(NULL),
	mCanPressStone(true),
	mSlashing(false),
	mCanPressSlash(true)
{	
	EntityManager::getInstance()->addEntity(mTelekinesisBox);
	mAnimation.init("Kiba.png", 60, 6);
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = KIBA;
	mPosition = position + sf::Vector2f(0, 38);
}


Kiba::~Kiba()
	{}

void Kiba::update(EntityKind &currentEntity)
{	
	move();
	slashing();

	if(mCanMove)
	{
		if(currentEntity == mEntityKind)
		{
			if(mTeleState == NOSTONE && !mSlashing)
			{
				walk();
				jump();
				slash();

				noStone();			
			}
			else
			{
				choosing();
				selectedStone();
			}
		}
		else
		{
			if(mStone != NULL)
			{
				mStone->setMoveing(false);
			}
		}
	}

	Character::update(currentEntity);
	mTelekinesisBox->setPosition(mPosition);

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		mCanPressStone = true;
	}
}




void Kiba::render()
{
	sf::RenderStates states;
	if(mHurtShow)
	{
		states.shader = &mHurtShader;
	}
	
	mAnimation.update(mStatus * 2 + mDirLeft);

	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -68));
	ImageManager::render(&mAnimation.getSprite(), states);
}





void Kiba::slash()
{ 
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mslashtimer.getElapsedTime().asSeconds() >= 0.6 && !mJumping && !mFalling && mCanPressSlash)
	{	
		mCanPressSlash = false;

		mslashtimer.restart();
		Slash *slash = new Slash(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 32, mPosition.y - 30), mDirLeft);
		EntityManager::getInstance()->addEntity(slash);
		Sounds::getInstance()->Play("slash.wav", 30);
		mStatus = ACTION2;
		mAnimationClock.restart();
		
		mMovementSpeed.x = 0;
		mSlashing = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		mCanPressSlash = true;
	}
}

// tre olika states för selected stone
// när man inte har någon sten
void Kiba::noStone()
{
	if(mTeleState == NOSTONE)
	{
		mTelekinesisBox->clear();

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressStone && !mFalling && !mJumping)
		{
			mCanPressStone = false;

			mTeleState = CHOOSING;
		}
	}
}

// när man väljer mellan olika stenar
void Kiba::choosing()
{
	if(mTeleState == CHOOSING)
	{
		// kollar om det bara finns en sten i vektorn
		if(mTelekinesisBox->getNumberOfStones() != 0)
		{
			if(mTelekinesisBox->getNumberOfStones() == 1)
			{
				mStone = mTelekinesisBox->getCurrentStone();

				if(mStone != NULL)
				{
					mStone->setStoneState(Stone::INAIR);
					mTeleState = SELECTEDSTONE;
					Sounds::getInstance()->Play("levitate.wav", 80);
				}
			}
			else
			{
				// byt sten
				mTelekinesisBox->getCurrentStone()->setStoneState(Stone::ONGROUND);
			
				mTelekinesisBox->changeCurrenStone();// ändrar sten
			
				mTelekinesisBox->getCurrentStone()->setStoneState(Stone::SELECTED);
			}

			mStatus = ACTION1;
			mMovementSpeed.x = 0;
		}
		else
		{
			mTeleState = NOSTONE;
			Sounds::getInstance()->Play("errorsound.wav", 30);
		}


		// kollaar knaptryck
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mCanPressStone && mTelekinesisBox->getNumberOfStones() != 0)
		{
			mCanPressStone = false;
			
			mStone = mTelekinesisBox->getCurrentStone();
			mTeleState = SELECTEDSTONE;
			Sounds::getInstance()->Play("levitate.wav", 80);
			
			if(mStone != NULL)
			{	
				mStone->setStoneState(Stone::INAIR);	
			}
		}
	}
}

// när man har en sten som man flyttar runt
void Kiba::selectedStone()
{
	if(mTeleState == SELECTEDSTONE)
	{
		mStatus = ACTION1;
		if(mStone != NULL)
		{
			mStone->setKibaPos(mPosition);
			mStone->move();
			mStone->setMoveing(true);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mCanPressStone)
		{
			mCanPressStone = false;

			if(mStone != NULL && mStone->getOnBlock())
			{
				mTeleState = NOSTONE;
				mStone->setStoneState(Stone::ONGROUND);
				mStone->setMoveing(false);
				mStone == NULL;
			}
			else
			{
				Sounds::getInstance()->Play("errorsound.wav", 30);
			}
		}
	}
}

// omdefinerar
void Kiba::onblock()
{
	if(mFalling)
	{
		mFalling = false;
		if(mStatus == INAIR)
		{
			mStatus = IDLE;

			if(mMovementSpeed.y > 1 && mMovementSpeed.y < 8)
			{
				Sounds::getInstance()->Play("jump2.wav", 20);
				Sounds::getInstance()->Play("land.wav", 30);
			}
			else if(mMovementSpeed.y >= 8)
			{
				Sounds::getInstance()->Play("land.wav", 70);
				Sounds::getInstance()->Play("land.wav", 30);
			}
		}
		mMovementSpeed.y = 0;
	}
	if(mAnimationClock.getElapsedTime().asMilliseconds() > 300)
	{
		if(mStatus == ACTION2 && mAnimation.getEndOfAnimation() || (mStatus == JUMP && !mJumping) || (mStatus == ACTION1 && mAnimation.getEndOfAnimation() && mTeleState == NOSTONE))
		{		
			mStatus = IDLE;
		}
	}
}

void Kiba::slashing()
{
	if(mslashtimer.getElapsedTime().asSeconds() > 0.6)
	{
		mSlashing = false;
	}
}