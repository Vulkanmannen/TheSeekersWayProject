#ifndef	INCLUDED_TUTORIALSIGN
#define INCLUDED_TUTORIALSIGN

#include "Object.h"


class TutorialSign: public Object
{
public:
	TutorialSign(sf::Vector2f &position);
	~TutorialSign();

	void update(EntityKind &currentEntity);
	void render();
	void interact(Entity* e);

private:

	sf::Clock mClock;
	sf::Texture mZoomedSignTexture;
	sf::Sprite mZoomedSignSprite;

	void onSignFalse();

	bool kibaOnSign;
	bool charlotteOnSign;
	bool fenrirOnSign;
	bool sheekaOnSign;
};

#endif