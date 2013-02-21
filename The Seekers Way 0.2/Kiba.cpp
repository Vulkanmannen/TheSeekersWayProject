#include "Kiba.h"
#include "Animation.h"
#include "ImageManager.h"
#include "Sounds.h"
#include <iostream>
const static float HEIGHT = 128;
const static float WIDTH = 56;

Kiba::Kiba(sf::Vector2f &position):
	telestate(free),
	mTeleBox(new TelekinesisBox(position))	
{	
	mStone=0;
	EntityManager::getInstance()->addEntity(mTeleBox);
	mAnimation.init("Kiba.png", 60, 6);
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = KIBA;
	mPosition = position;
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

			else if(telestate == moving)
			{
				telekinesis();
			}

			if(teletimer.getElapsedTime().asMilliseconds() > 500)
			{
				if(telestate == choice)
				{
					if(mTeleBox->stone.size() != 0)
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
						{	
							mTeleBox->getStone(-1);
							teletimer.restart();
						}
						else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
						{
							mTeleBox->getStone(1);
							teletimer.restart();
						}
						
					}
				}

				// en function
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					teletimer.restart();

					if(telestate == choice)
					{ 
						telestate = moving;
					
						if(mTeleBox->stone.size() != 0)
						{
							mStone = mTeleBox->getStone();
						}
						else 
						{
							telestate = free;
						}
					}

					else if(telestate == moving && mStone->onblock())
					{
						telestate = free;
						if(mStone->mtelekinesis != false)
						{
							mStone->mtelekinesis = false;
						}
					}

					else if(telestate == free)
					{
						telestate = choice;

						mTeleBox->setPosition(mPosition);
					}
				}
			}
		}
		else if(mStone != 0)
		{
			if(mStone->mtelemove != false)
			{
				mStone->mtelemove = false;
			}
		}
	}
	
	Character::update(currentEntity);

	mTeleBox->stone.clear();
}


void Kiba::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -64));
	ImageManager::render(&mAnimation.getSprite());
}

void Kiba::telekinesis()
{
	if(mStone != 0)
	{
		int rad1 =	(mStone->getPosition() - getPosition()).x * 
					(mStone->getPosition() - getPosition()).x +
					(mStone->getPosition() - getPosition()).y * 
					(mStone->getPosition() - getPosition()).y ;
		int rad2 =	mTeleBox->getHeight() * 
					mTeleBox->getHeight() / 4 +
					mTeleBox->getWidth() *
					mTeleBox->getWidth() / 4;


		if(rad2 > rad1)
		{
			mStone->mtelekinesis = true;
			mStone->mtelemove = true;
			mStone->mKibaPos = mPosition;
		}
		else
		{
			mStone->mtelemove = false;
		}
	}
}

void Kiba::getStone()
{

}

void Kiba::slash()
{ 
	// tryck "Q" för att aktivera en sköld (1 sec cd)
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mslashtimer.getElapsedTime().asSeconds() >= 1)
	{	
		mslashtimer.restart();
		Slash *slash = new Slash(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 32, mPosition.y - 30), mDirLeft);
		EntityManager::getInstance()->addEntity(slash);
		Sounds::getInstance()->Play("slash.wav");
	}
}
