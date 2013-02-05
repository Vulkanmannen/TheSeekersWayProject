#include "Stone.h"
#include "ImageManager.h"

static const float WIDTH = 128;
static const float HEIGHT = 128;

Stone::Stone(sf::Vector2f Position):
	mMovementSpeed(0,0),
	mGravity(5),
	mDecrease(0.6),
	mFalling(false),
	mtelekinesis(false)
{
	mPosition = Position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = STONE;
	mTexture.loadFromImage(*ImageManager::getImage("crashstone.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(Position);
	mSprite.scale(WIDTH/mSprite.getTexture()->getSize().x,HEIGHT/mSprite.getTexture()->getSize().y);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}

Stone::~Stone()
{

}

void Stone::update(EntityKind &currentEntity)
{
	move();

	mtelekinesis ? telekinesis(), mBaseKind = OBJECT : falling(), mBaseKind = BLOCK;

	mFalling = true;
}

void Stone::render()
{
	mSprite.setPosition(sf::Vector2f(mPosition.x, mPosition.y));
	ImageManager::render(&mSprite);
}

void Stone::telekinesis()
{
	if(mMovementSpeed.x*mMovementSpeed.x+mMovementSpeed.y*mMovementSpeed.y < 10)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mMovementSpeed.x -= 1;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mMovementSpeed.x += 1;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mMovementSpeed.y -= 1;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mMovementSpeed.y += 1;
		}
	}
}

void Stone::move()	   
{
	mPosition	+= mMovementSpeed;
	mMovementSpeed -= sf::Vector2f( 0.1*mMovementSpeed.x, 0.1*mMovementSpeed.y);
}

void Stone::falling() 
{
	mPosition.y	+= mGravity;
	if(mFalling)
	{
		mMovementSpeed.y += mDecrease;
	}
}

void Stone::interact(Entity* e)
{
	if(e->getBaseKind() == Entity::BLOCK || (e->getBaseKind() == Entity::CHARACTER && mtelekinesis ))
	{

		// r�knar ut objektens radier och l�gger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// ber�knar differansen mellan tv� objekt
		float xDif = mPosition.x - e->getPosition().x;
		float yDif = mPosition.y - e->getPosition().y;

		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // �r karakt�ren h�ger/v�nster eller �ver/under om blocket
		{
			if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
				{
					mPosition -= sf::Vector2f(mPosition.x - (e->getPosition().x + xRadius - 3), 0);
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10)
				{
					mPosition -= sf::Vector2f(mPosition.x - (e->getPosition().x - (xRadius - 3)), 0);
				}
			}
		}
		else
		{
			if(yDif > 0) // kollar om karakt�ren �r under eller �ver
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett �ver
				{
					mPosition -= sf::Vector2f( 0,mPosition.y - (e->getPosition().y + yRadius));
					//mJumping = 0;
					//mIsJumping = false;
				}
			}
			else
			{
				if(std::abs(xDif) < xRadius - 10)
				{
					mPosition -= sf::Vector2f(0, mPosition.y - (e->getPosition().y - yRadius ));
					//mMovementSpeed.y = 0;
					//onblock();
					mFalling = false;
				}
			}
		}
	}
}