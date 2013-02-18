#include "Bridge.h"
#include "ImageManager.h"
#include "Character.h"

static const float WIDTH = 128;
static const float HEIGHT = 64;

Bridge::Bridge(sf::Vector2f &position, bool closed):
	mAnimation("Door2.png", 60, 1, HEIGHT, WIDTH),
	isitclosed(closed)
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
	mPosition = position + sf::Vector2f(32, 0);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BRIDGE;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

}

Bridge::~Bridge()
{

}

void Bridge::Activate()
{
	!isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::DisActivate()
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::update(EntityKind &currentEntity)
{

}

void Bridge::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

// knuffar charactärer
void Bridge::interact(Entity* e)
{
	if((*e) == CHARACTER && mBaseKind == BLOCK)
	{
		Character* c = static_cast<Character*>(e);

		// räknar ut objektens radier och lägger ihop dem
		float xRadius = mWidth / 2 + c->getWidth() / 2;
		float yRadius = mHeight / 2 + c->getHeight() / 2;

		// beräknar differansen mellan två objekt
		float xDif = c->getPosition().x - mPosition.x ;
		float yDif = c->getPosition().y - mPosition.y ;

		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif) > xRadius - 10) // kollar så blocket inte ligger snett under
		{
			if(xDif > 0) // kollar om karaktären är höger eller vänster
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