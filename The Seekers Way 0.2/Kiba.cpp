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
	mCanPressStone(true)
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
	
	if(mCanMove)
	{
		if(currentEntity == mEntityKind)
		{
			if(mTeleState == NOSTONE)
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

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
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
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mslashtimer.getElapsedTime().asSeconds() >= 1)
	{	
		mslashtimer.restart();
		Slash *slash = new Slash(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 32, mPosition.y - 30), mDirLeft);
		EntityManager::getInstance()->addEntity(slash);
		Sounds::getInstance()->Play("slash.wav", 30);
		mStatus = ACTION2;
	}
}

// tre olika states f�r selected stone
// n�r man inte har n�gon sten
void Kiba::noStone()
{
	if(mTeleState == NOSTONE)
	{
		mTelekinesisBox->clear();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mCanPressStone && !mFalling && !mJumping)
		{
			mCanPressStone = false;

			mTeleState = CHOOSING;
		}
	}
}

// n�r man v�ljer mellan olika stenar
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
					Sounds::getInstance()->Play("levitate.wav");
				}
			}
			else
			{
				// byt sten
				mTelekinesisBox->getCurrentStone()->setStoneState(Stone::ONGROUND);
			
				mTelekinesisBox->changeCurrenStone();// �ndrar sten
			
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
			Sounds::getInstance()->Play("levitate.wav");
			
			if(mStone != NULL)
			{	
				mStone->setStoneState(Stone::INAIR);	
			}
		}
	}
}

// n�r man har en sten som man flyttar runt
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

			if(mMovementSpeed.y > 1)
			{
				Sounds::getInstance()->Play("land.wav", 70);
			}
		}
		mMovementSpeed.y = 0;
	}

	if(mStatus == ACTION2 && mAnimation.getEndOfAnimation() || (mStatus == JUMP && !mJumping) || (mStatus == ACTION1 && mAnimation.getEndOfAnimation() && mTeleState != SELECTEDSTONE))
	{
		mStatus = IDLE;
	}
}