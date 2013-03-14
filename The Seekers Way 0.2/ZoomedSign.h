#ifndef INCLUDED_ZOOMEDSIGN
#define INCLUDED_ZOOMEDSIGN

#include "Object.h"

class ZoomedSign: public Object
{
public:
	ZoomedSign(sf::Vector2f &position, unsigned char spriteNumber);
	~ZoomedSign();

	void update(EntityKind &currentEntity);
	void render();
	void setCharacterOnSign(bool);

private:

	sf::Texture mZoomedSignTexture;
	sf::Sprite mZoomedSignSprite;

	bool mCharacterOnSign;
};

#endif