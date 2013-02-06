#include "Kiba.h"
#include "Animation.h"
#include "ImageManager.h"

const static float HEIGHT = 128;
const static float WIDTH = 64;

Kiba::Kiba(sf::Vector2f &position):
	telestate(free)
{
	mAnimation.init("fenrir.png", 60, 7);
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = KIBA;
	mPosition = position;
}


Kiba::~Kiba()
	{}

void Kiba::update(EntityKind &currentEntity)
{
	if(currentEntity == mEntityKind && telestate == free)
	{
		walk();
		jump();

		// en function
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && teletimer.getElapsedTime().asMilliseconds() > 500)
		{
			telestate = tele((int(telestate) + 1) % 3);
			teletimer.restart();

			telestate == choice ? mTeleBox = new TelekinesisBox(mPosition) : NULL ;
		}

	}

	else if(telestate == moving)
	{
		telekinesis();
	}

	else if(telestate == choice)
	{
		getStone();
	}
	

	dontWalk(currentEntity);
	move();
	jumping();
	falling();
	fall();
}


void Kiba::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -64));
	ImageManager::render(&mAnimation.getSprite());
}

void Kiba::telekinesis()
{

}

void Kiba::getStone()
{

}