#include "Spiketrap.h"
#include "ImageManager.h"

static const float HEIGHT = 128;
static const float WIDTH = 64;

Spiketrap::Spiketrap(sf::Vector2f &position)
	
{
	mPosition = position + sf::Vector2f(0,32);
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = SPIKETRAP;

}


Spiketrap::~Spiketrap()
{

}