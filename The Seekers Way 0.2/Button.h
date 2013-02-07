#ifndef INCLUDED_Button
#define INCLUDED_Button

#include "Block.h"
#include "Animation.h"

class Button: public Block
{
public:

	Button(sf::Vector2f &position, Block* target);
	~Button();

	void render();
	void update(EntityKind &currentEntity);
	void interact(Entity* e);

	void Activate();
	void DisActivate();

private:
	Animation mAnimation;

	Block* mBlock;
	bool isitpressed;
};

#endif