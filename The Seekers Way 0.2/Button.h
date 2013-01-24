#ifndef INCLUDED_Button
#define INCLUDED_Button

#include "Block.h"
#include "Door.h"

class Button: public Block
{
public:

	Button(sf::Vector2f &position, int id);
	~Button();
	Block* mBlock;

	void ButtonPressed();
	void ButtonRelease();
	bool isitpressed;
};

#endif