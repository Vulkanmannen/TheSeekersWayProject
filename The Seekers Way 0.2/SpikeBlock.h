#ifndef INCLUDED_SPIKEBLOCK
#define INCLUDED_SPIKEBLOCK

#include "Block.h"
#include "Animation.h"

class SpikeBlock: public Block
{
public:
	SpikeBlock(sf::Vector2f &position);
	~SpikeBlock();

	void render();
	void update(EntityKind &currentEntity);

	void interact(Entity* e);

private:
	Animation mAnimation;
	void Spike();
};

#endif