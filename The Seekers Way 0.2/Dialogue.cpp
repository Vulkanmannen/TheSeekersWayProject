#include "Dialogue.h"

Dialogue* Dialogue::sInstance = 0;

Dialogue::Dialogue():
	text("sfml")
{

}

Dialogue::~Dialogue()
{

}

Dialogue* Dialogue::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new Dialogue;
	}
	return sInstance;
}

void Dialogue::update()
{

}

void Dialogue::render()
{
	dWindow->draw(text);
}

void Dialogue::setWindow(sf::RenderWindow *window)
{
	dWindow = window;
}