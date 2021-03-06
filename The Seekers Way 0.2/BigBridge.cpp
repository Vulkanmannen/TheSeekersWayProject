#include "BigBridge.h"
#include "ImageManager.h"
#include <cmath>
#include "Character.h"
#include "Sounds.h"

static const float WIDTH = 320;
static const float HEIGHT = 32;

BigBridge::BigBridge(sf::Vector2f &position, bool closed):
	mAnimation("bigbridge.png", 30, 9, HEIGHT, WIDTH),
	isitclosed(closed)
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
	mPosition = position + sf::Vector2f(WIDTH/2 - 32, 0);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BIGBRIDGE;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

	if(isitclosed)
	{
		mStatus = CLOSED;
	}
	else
	{
		mStatus = OPEN;
	}
}

BigBridge::~BigBridge()
{

}

void BigBridge::Activate()
{
	if(isitclosed)
	{
		if(mStatus != OPEN)
		{
			mStatus = OPENING;
			mAnimationClock.restart();

			if(mSoundClock.getElapsedTime().asSeconds() > 1.2)
			{
				Sounds::getInstance()->Play("door.wav");
				mSoundClock.restart();
			}
		}
	}
	else
	{
		if(mStatus != CLOSED)
		{
			mStatus = CLOSING;
			mAnimationClock.restart();
			
			if(mSoundClock.getElapsedTime().asSeconds() > 1.2)
			{
				Sounds::getInstance()->Play("door.wav");
				mSoundClock.restart();
			}
		}
	}
	!isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void BigBridge::DisActivate()
{
	if(!isitclosed)
	{
		if(mStatus != OPEN)
		{
			mStatus = OPENING;
			mAnimationClock.restart();
			
			if(mSoundClock.getElapsedTime().asSeconds() > 1.2)
			{
				Sounds::getInstance()->Play("door.wav");
				mSoundClock.restart();
			}
		}
	}
	else
	{
		if(mStatus != CLOSED)
		{
			mStatus = CLOSING;
			mAnimationClock.restart();
			
			if(mSoundClock.getElapsedTime().asSeconds() > 1.2)
			{
				Sounds::getInstance()->Play("door.wav");
				mSoundClock.restart();
			}
		}
	}
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void BigBridge::update(EntityKind &currentEntity)
{
	if(mStatus == OPENING && mAnimation.getEndOfAnimation() && mAnimationClock.getElapsedTime().asMilliseconds() > 300)
	{
		mStatus = OPEN;
	}

	if(mStatus == CLOSING && mAnimation.getEndOfAnimation() && mAnimationClock.getElapsedTime().asMilliseconds() > 300)
	{
 		mStatus = CLOSED;
	}
	mAnimation.update(mStatus);
}

void BigBridge::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

// knuffar charact�rer
void BigBridge::interact(Entity* e)
{
	if(((*e) == CHARACTER || (*e) == STONE) &&  mBaseKind == BLOCK)
	{

		
		// r�knar ut objektens radier och l�gger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// ber�knar differansen mellan tv� objekt
		float xDif = e->getPosition().x - mPosition.x ;
		float yDif = e->getPosition().y - mPosition.y ;

		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif) > xRadius - 10) // kollar s� blocket inte ligger snett under
		{
			if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
				{
					e->setPosition(sf::Vector2f(mPosition.x + xRadius - 0, e->getPosition().y));
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
				{
					e->setPosition(sf::Vector2f(mPosition.x - (xRadius - 0), e->getPosition().y));
				}
			}
		}
		else
		{


			if((*e == CHARACTER))	
			{
				Character* c = static_cast<Character*>(e);

				if(std::abs(yDif) > yRadius - 10 || c->getMovementSpeed().y > 4)
				{
					if(yDif > 0)
					{
						c->setPosition(sf::Vector2f(c->getPosition().x, mPosition.y + (yRadius + 0.1)));
						c->hitBlockFromBelow();
					}
					else
					{
						c->setPosition(sf::Vector2f(c->getPosition().x, mPosition.y - (yRadius - 0)));
						c->onblock();
					}
				}
				else
				{
					if(yDif > 0)
					{
						e->setPosition(e->getPosition() + sf::Vector2f(0, 4));
					}
					else
					{
						e->setPosition(e->getPosition() - sf::Vector2f(0, 4));
					}
				}
			}
			else
			{
				if(std::abs(yDif) > yRadius - 10)
				{
					if(yDif > 0)
					{
						e->setPosition(sf::Vector2f(e->getPosition().x, mPosition.y + (yRadius - 0)));
					}
					else
					{
						e->setPosition(sf::Vector2f(e->getPosition().x, mPosition.y - (yRadius - 0)));
					}
				}
				else
				{
					if(yDif > 0)
					{
						e->setPosition(e->getPosition() + sf::Vector2f(0, 4));
					}
					else
					{
						e->setPosition(e->getPosition() - sf::Vector2f(0, 4));
					}
				}
			}
		}
	}
}