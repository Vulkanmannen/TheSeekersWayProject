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

// knuffar charact�rer
void Bridge::interact(Entity* e)
{
	if(((*e) == CHARACTER || (*e) == STONE) &&  mBaseKind == BLOCK)
	{
		Character* c = static_cast<Character*>(e);

		// r�knar ut objektens radier och l�gger ihop dem
		float xRadius = mWidth / 2 + c->getWidth() / 2;
		float yRadius = mHeight / 2 + c->getHeight() / 2;

		// ber�knar differansen mellan tv� objekt
		float xDif = c->getPosition().x - mPosition.x ;
		float yDif = c->getPosition().y - mPosition.y ;

		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif) > xRadius - 10) // kollar s� blocket inte ligger snett under
		{
			if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
			{
				c->setPosition(sf::Vector2f(mPosition.x + xRadius - 0, c->getPosition().y));
			}
			else
			{
				c->setPosition(sf::Vector2f(mPosition.x - (xRadius - 0), c->getPosition().y));
			}
		}
		else
		{

			if(std::abs(yDif) > yRadius - 10)
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
					c->setPosition(c->getPosition() + sf::Vector2f(0, 4));
				}
				else
				{
					c->setPosition(c->getPosition() - sf::Vector2f(0, 4));
				}
			}
		}
	}
}