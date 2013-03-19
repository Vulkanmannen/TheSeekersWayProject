#include "Arrow.h"
#include "ImageManager.h"
#include "Sounds.h"

static const float WIDTH = 64;
static const float HEIGHT = 12;

Arrow::Arrow(sf::Vector2f &position, bool dirleft):
	mAnimation("arrow.png", 60, 9, HEIGHT, WIDTH),
	mWhole(false),
	mArrowBroken(false),
	mDirLeft(dirleft),
	mMovementSpeed(10*((0.5-dirleft)*2),0)
{
	mEntityKind = ARROW;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = Entity::ARROW;
	mPosition = position;
	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	mAnimation.update(mDirLeft);

	//mTexture.loadFromImage(*ImageManager::getImage("arrow.png"));
	//mSprite.setTexture(mTexture);
	//mSprite.setPosition(position);
	//mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	//mSprite.scale((-(0.5-dirleft)*2),1);
}

Arrow::~Arrow()
{

}

void Arrow::update(EntityKind &currentEntity)
{	
	mPosition	+= mMovementSpeed;
	mAnimation.update(mAnimation.getEndOfAnimation());
	if(!mWhole && mAnimation.getEndOfAnimation())
	{
		mWhole = true;
	}
	if(mArrowBroken && mAnimation.getEndOfAnimation() && mArrowBrokenClock.getElapsedTime().asMilliseconds() > 500)
	{
		destroy();
	}

	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
	//mSprite.setPosition(mPosition);
}

void Arrow::interact(Entity* e)
{
	if(mShottingTime.getElapsedTime().asMilliseconds() > 500 || (*e) != Entity::NORMALBLOCK)
	{
		switch(e->getEntityKind())
		{
		case SHIELD:
			Sounds::getInstance()->Play("arrowtoshield.wav", 70, mPosition);
		}
		if((*e) == Entity::BLOCK || (*e) == Entity::CHARACTER || (*e) == Entity::SHIELD || (*e) == Entity::STONE /*|| (*e) == SLASH*/)
		{
			if(e->getEntityKind() != FENRIR)
			{
				destroy();
			}
		}
	}
}

void Arrow::killArrow()
{
	mArrowBroken = true;
	mArrowBrokenClock.restart();
}