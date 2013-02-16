#ifndef INCLUDED_LAMA
#define INCLUDED_LAMA

#include "Block.h"
#include "Animation.h"
#include "SFML\Graphics.hpp"

class Lava : public Block
{
public:
	Lava(sf::Vector2f &position);
	~Lava();

	void update(EntityKind &currentEntity);
	void render();
private:
	Animation mAnimation;
};

#endif