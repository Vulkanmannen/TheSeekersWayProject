#include "Stone.h"
#include "ImageManager.h"
#include <math.h>
#include "TelekinesisBox.h"

static const float WIDTH = 128;
static const float HEIGHT = 128;

static const float SPRITEWIDTH = 140;
static const float SPRITEHEIGHT = 140;

Stone::Stone(sf::Vector2f Position):
	mAnimation("stone.png", 80, 6, SPRITEHEIGHT, SPRITEWIDTH),
	mMoveing(false),
	mOnBlock(true),
	mRange(288),
	mStoneState(ONGROUND),
	mKibaPos(sf::Vector2f(0, 0)),
	mMoveSpeed(5),
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
	if(mMoveing)
	{
		mBaseKind = OBJECT;
	}
	else
	{
		mBaseKind = BLOCK;
	}

	mAnimation.update(mStoneState);
	mOnBlock = false;
}

void Stone::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}


void Stone::interact(Entity* e)
{
	// r�knar ut objektens radier och l�gger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// ber�knar differansen mellan tv� objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;

	if((*e == CHARACTER) && yDif > yRadius - 20)
	{
		mCharacterOnStone = true;
	}

	if(((	*e) == BLOCK || *e == CHARACTER) && (*e) != DOOR && (*e) != BRIDGE && (*e) != BIGBRIDGE &&	mMoveing && !mCharacterOnStone)
	{
		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // �r karakt�ren h�ger/v�nster eller �ver/under om blocket
		{
			if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
				{
					mPosition = sf::Vector2f(e->getPosition().x + xRadius - 3, mPosition.y);
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10)
				{
					mPosition = sf::Vector2f(e->getPosition().x - (xRadius - 3), mPosition.y);
				}
			}
		}
		else
		{
			if(yDif > 0) // kollar om karakt�ren �r under eller �ver
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett �ver
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y + yRadius);

					if(*e == CHARACTER)
					{
						mCharacterOnStone = true;
					}
					else if(*e == STONE)
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
					mOnBlock = true;
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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mPosition.y - mKibaPos.y < mRange)
	{
		mPosition.y += mMoveSpeed;
		mOnBlock = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mPosition.x - mKibaPos.x < mRange && !mCharacterOnStone && !mStoneOnStone)
	{
		mPosition.x += mMoveSpeed;
		mOnBlock = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mKibaPos.x - mPosition.x < mRange && !mCharacterOnStone && !mStoneOnStone)
	{
		mPosition.x -= mMoveSpeed;
		mOnBlock = false;
	}
}
