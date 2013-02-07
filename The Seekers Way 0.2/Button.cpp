#include "Button.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Button::Button(sf::Vector2f &position, Block* target):
	mBlock(target),
	mAnimation("Button.png", 60, 1, HEIGHT, WIDTH)
{
	isitpressed = false;
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BUTTON;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}

Button::~Button()
{

}

void Button::Activate()
{
	if(isitpressed == false)
	{
		mBlock->Activate();
	}
	isitpressed = true;
}

void Button::DisActivate()
{
	if(isitpressed == false)
	{
		mBlock->DisActivate();
	}
	isitpressed = false;
}

void Button::update(EntityKind &currentEntity)
{
	DisActivate();
}

void Button::render()
{
	mAnimation.update(isitpressed);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Button::interact(Entity* e)
{
	if(getPosition().y - e->getPosition().y > (e->getHeight() / 2 + mHeight / 2) - 7)
	{
		switch(e->getEntityKind())
		{
		case CHARLOTTE:
		case KIBA:
		case FENRIR:
		case SHEEKA:
		case STONE:
			Activate();
			break;
		}
	}
}