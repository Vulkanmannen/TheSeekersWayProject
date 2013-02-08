#ifndef INCLUDED_TelekinesisBox
#define INCLUDED_TelekinesisBox
#include "Animation.h"
#include "Object.h"
#include "Stone.h"


class TelekinesisBox: public Object
{
public:
	TelekinesisBox(sf::Vector2f &position);

	~TelekinesisBox();

	void render();
	void update(EntityKind &currentEntity);
	void interact(Entity* e);
	Stone* getStone(int a = 0);
	int b;
	std::vector<Stone*> stone;

private:
	
};

#endif