#ifndef INCLUDED_Stone
#define INCLUDED_Stone

#include "Block.h"
#include "SFML\Graphics.hpp"
#include "Animation.h"


class Stone: public Block
{
public:
	Stone(sf::Vector2f Position);
	~Stone();
	void update(EntityKind &currentEntity);
	void render();
	void interact(Entity* e);

	enum StoneState {ONGROUND, INAIR, SELECTED};
	
	void setStoneState(StoneState);
	void setMoveing(bool moving);
	void setKibaPos(sf::Vector2f kibaPos);

	bool getOnBlock()const;

	void move();
private:
	Animation mAnimation;

	sf::Vector2f mKibaPos;
	float mRange;

	StoneState mStoneState;

	bool mMoveing;
	bool mCharacterOnStone;
	bool mStoneOnStone;
	bool mOnBlock;

	float mMoveSpeed;
};

#endif