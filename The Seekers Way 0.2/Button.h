#ifndef INCLUDED_Button
#define INCLUDED_Button

#include "Block.h"
#include "Animation.h"

class Button: public Block
{
public:

	Button(sf::Vector2f &position, Block* target);
	~Button();
	Block* mBlock;

	void render();
	void update();
	sf::Sprite getSprite();

	void Activate();
	void DisActivate();

	bool isitpressed;
private:
	Animation mAnimation;
};

#endif