#ifndef INCLUDED_TelekinesisBox
#define INCLUDED_TelekinesisBox
#include "Animation.h"
#include "Object.h"
#include "Stone.h"


class TelekinesisBox: public Object
{
public:
	typedef std::vector<Stone*> StoneVector;

	TelekinesisBox(sf::Vector2f &position, Stone*);

	~TelekinesisBox();

	void render();
	void update(EntityKind &currentEntity);
	void interact(Entity* e);
	Stone* getStone();
	void changeStone();

	StoneVector getStoneVector()const;

	void clearStoneVector();

private:
	int mSelectedStone;
	StoneVector stone;

	Stone* mNoStone;

	bool mCanPressChange;
};

#endif