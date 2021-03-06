#include "Button.h"
#include "ImageManager.h"
#include "Sounds.h"

static const float WIDTH = 45;
static const float HEIGHT = 5;

static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 64;

Button::Button(sf::Vector2f &position, Block* target):
	mBlock(target),
	mAnimation("button.png", 60, 1, SPRITEHEIGHT, SPRITEWIDTH),
	collision(false)
{
	isitpressed = false;
	mPosition = position + sf::Vector2f(0, 29);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BUTTON;
	mAnimation.setPosition(sf::Vector2f(position.x - SPRITEWIDTH/ 2, position.y - SPRITEHEIGHT/ 2));
}

Button::~Button()
{

}

void Button::Activate()
{
	if(isitpressed == false)
	{
		mBlock->Activate();
		isitpressed = true;
		Sounds::getInstance()->Play("button.wav", 30);
	}	
}

void Button::DisActivate()
{
	if(isitpressed == true)
	{
		mBlock->DisActivate();
		isitpressed = false;
	}
	
}

void Button::update(EntityKind &currentEntity)
{
	collision ? Activate() : DisActivate();
	collision = false;
}

void Button::render()
{
	mAnimation.update(isitpressed);
	ImageManager::render(&mAnimation.getSprite());
}

void Button::interact(Entity* e)
{
	switch(e->getEntityKind())
	{
	case CHARLOTTE:
	case KIBA:
	case FENRIR:
	case SHEEKA:
	case STONE:
		collision = true;
		break;
	}
}