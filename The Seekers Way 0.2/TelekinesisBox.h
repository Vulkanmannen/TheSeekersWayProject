#ifndef INCLUDED_TelekinesisBox
#define INCLUDED_TelekinesisBox
#include "Animation.h"
#include "Object.h"
#include "Stone.h"


class TelekinesisBox: public Object
{
public:
	typedef std::vector<Stone*> StoneVector;

	TelekinesisBox(sf::Vector2f &position);

	~TelekinesisBox();

	void render();
	void update(EntityKind &currentEntity);
	void interact(Entity* e);

	void changeCurrenStone();
	Stone* getCurrentStone();
	void clear();

	int getNumberOfStones()const;
private:
	StoneVector mStones;
	int mCurrentStone;
	
	bool mCanPressChange;
	bool mCanPressClear;
};

#endif