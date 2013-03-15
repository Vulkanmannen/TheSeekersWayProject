#include "Stone.h"
#include "ImageManager.h"
#include <math.h>
#include "TelekinesisBox.h"

static const float WIDTH = 124;
static const float HEIGHT = 124;

static const float SPRITEWIDTH = 140;
static const float SPRITEHEIGHT = 140;

Stone::Stone(sf::Vector2f Position):
	mAnimation("stone.png", 80, 6, SPRITEHEIGHT, SPRITEWIDTH),
	mMoveing(false),
	mOnBlock(true),
	mRange(288),
	mStoneState(ONGROUND),
	mKibaPos(sf::Vector2f(0, 0)),
	mMoveSpeed(3),
	mCharacterOnStone(false),
	mStoneOnStone(false)
{
	mPosition = Position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = STONE;
	mLayer = FORGROUND;

	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
}

Stone::~Stone()
{

}

void Stone::update(EntityKind &currentEntity)
{
	if(mMoveing && !mCharacterOnStone)
	{
		mBaseKind = OBJECT;
	}
	else
	{
		mBaseKind = BLOCK;
	}

	mAnimation.update(mStoneState);

	mOnBlock = false;
	mCharacterOnStone = false;
	mStoneOnStone = false;
}

void Stone::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}


void Stone::interact(Entity* e)
{
	// räknar ut objektens radier och lägger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// beräknar differansen mellan två objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;

	if(*e == KIBA && yDif > yRadius - 20 && mMoveing)
	{
		mPosition = sf::Vector2f(mPosition.x, e->getPosition().y + yRadius + 0.1);
	}

	if((*e == CHARACTER) && yDif > yRadius - 20)
	{
		mCharacterOnStone = true;
	}

	if(*e == BLOCK && *e != DOOR && *e != BRIDGE && *e != BIGBRIDGE || *e == CHARACTER && mMoveing && !mCharacterOnStone)
	{
		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // är karaktären höger/vänster eller över/under om blocket
		{
			if(xDif > 0) // kollar om karaktären är höger eller vänster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
				{
					mPosition = sf::Vector2f(e->getPosition().x + xRadius, mPosition.y);
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10)
				{
					mPosition = sf::Vector2f(e->getPosition().x - (xRadius), mPosition.y);
				}
			}
		}
		else
		{
			if(yDif > 0) // kollar om karaktären är under eller över
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett över
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y + yRadius);

					if(*e == STONE)
					{
						mStoneOnStone = true;
					}
				}
			}
			else
			{
				if(std::abs(xDif) < xRadius - 10)
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y - yRadius);
					if(*e == BLOCK)
					{
						mOnBlock = true;
					}
				}
			}
		}
	}
}

void Stone::setStoneState(StoneState stoneState)
{
	mStoneState = stoneState;
}

void Stone::setMoveing(bool moveing)
{
	mMoveing = moveing;
}

void Stone::setKibaPos(sf::Vector2f kibaPos)
{
	mKibaPos = kibaPos;
}

bool Stone::getOnBlock()const
{
	return mOnBlock;
}

void Stone::move()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mKibaPos.y - mPosition.y < mRange && !mCharacterOnStone && !mStoneOnStone)
	{
		mPosition.y -= mMoveSpeed;
		mOnBlock = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mPosition.y - mKibaPos.y < mRange && !mCharacterOnStone && !mOnBlock)
	{
		mPosition.y += mMoveSpeed;
		mOnBlock = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mPosition.x - mKibaPos.x < mRange && !mCharacterOnStone && (!mStoneOnStone || !mOnBlock))
	{
		mPosition.x += mMoveSpeed;
		mOnBlock = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mKibaPos.x - mPosition.x < mRange && !mCharacterOnStone && (!mStoneOnStone || !mOnBlock))
	{
		mPosition.x -= mMoveSpeed;
		mOnBlock = false;
	}
}
