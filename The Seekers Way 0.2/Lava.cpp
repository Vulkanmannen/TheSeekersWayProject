#include "Lava.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 50;

static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 64;

Lava::Lava(sf::Vector2f & position):
	mAnimation("lava.png", 80, 5, SPRITEHEIGHT, SPRITEWIDTH)
	{
	mPosition = position + sf::Vector2f(0, 7);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = LAVA;

	mAnimation.setPosition(sf::Vector2f(position.x - SPRITEWIDTH/ 2, position.y - SPRITEHEIGHT/ 2));
	}


Lava::~Lava()
	{}

void Lava::update(EntityKind &currentEntity)
{
	mAnimation.update(0);
}

void Lava::render()
{
	ImageManager::render(&mAnimation.getSprite());
}