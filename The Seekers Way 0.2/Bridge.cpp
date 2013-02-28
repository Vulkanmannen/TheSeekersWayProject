#include "Bridge.h"
#include "ImageManager.h"
#include "Character.h"

static const float WIDTH = 128;
static const float HEIGHT = 32;

Bridge::Bridge(sf::Vector2f &position, bool closed):
	mAnimation("bridge.png", 30, 10, HEIGHT, WIDTH),
	isitclosed(closed)
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
	mPosition = position + sf::Vector2f(32, 0);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BRIDGE;
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

Bridge::~Bridge()
{

}

void Bridge::Activate()
{
	if(isitclosed)
	{
		if(mStatus != OPEN)
		{
			mStatus = OPENING;
		}
	}
	else
	{
		if(mStatus != CLOSED)
		{
			mStatus = CLOSING;
		}
	}
	!isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::DisActivate()
{
	if(!isitclosed)
	{
		if(mStatus != OPEN)
		{
			mStatus = OPENING;
		}
	}
	else
	{
		if(mStatus != CLOSED)
		{
			mStatus = CLOSING;
		}
	}
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::update(EntityKind &currentEntity)
{
	if(mStatus == OPENING && mAnimation.getEndOfAnimation())
	{
		mStatus = OPEN;
	}

	if(mStatus == CLOSING && mAnimation.getEndOfAnimation())
	{
 		mStatus = CLOSED;
	}
}

void Bridge::render()
{
	mAnimation.update(mStatus);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

// knuffar charactärer
void Bridge::interact(Entity* e)
{
	if(((*e) == CHARACTER || (*e) == STONE) &&  mBaseKind == BLOCK)
	{

		
		// räknar ut objektens radier och lägger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// beräknar differansen mellan två objekt
		float xDif = e->getPosition().x - mPosition.x ;
		float yDif = e->getPosition().y - mPosition.y ;

		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif) > xRadius - 10) // kollar så blocket inte ligger snett under
		{
			if(xDif > 0) // kollar om karaktären är höger eller vänster
			{
				e->setPosition(sf::Vector2f(mPosition.x + xRadius - 0, e->getPosition().y));
			}
			else
			{
				e->setPosition(sf::Vector2f(mPosition.x - (xRadius - 0), e->getPosition().y));
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
						c->setPosition(sf::Vector2f(c->getPosition().x, mPosition.y + (yRadius - 0)));
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