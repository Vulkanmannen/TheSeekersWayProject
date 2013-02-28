#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "SFML\Graphics.hpp"

class Entity
{
public:
	enum EntityKind {
		KIBA, CHARLOTTE, FENRIR, SHEEKA,
		NORMALBLOCK, BUTTON, DOOR, STONE, BROKENWALL, 
		SHOTTINGTRAP, WALLTRAP, WOODENWALL, VINE, SPIKETRAP,
		FLOORTRAP, ARROW, SHIELD, PORTAL, LEVER,
		FIREBALL, FIRERUNE, DARKBINDING, MAGICSWITCH, SPIKEBLOCK, 
		BRIDGE, BIGBRIDGE, TELEKINESISBOX, LAVA, SLASH, FINISHDOOR, DECORATION};

	enum BaseKind {CHARACTER, BLOCK, OBJECT};

	enum Layer {BACKGROUND, MIDDLE, CHARACTERS, FORGROUND};

	Entity();
	virtual ~Entity();

	virtual void update(EntityKind &currentEntity) = 0;

	virtual void interact(Entity* e) = 0;

	virtual void render();
	
	sf::Vector2f getPosition()const;
	float getTop()const;
	float getBottom()const;
	float getRight()const;
	float getLeft()const;
	float getWidth()const;
	float getHeight()const;
	EntityKind getEntityKind()const;
	BaseKind getBaseKind()const;
	Layer getLayer()const;

	bool getAliveStatus()const;

	void destroy();

	void setPosition(sf::Vector2f &v);

	bool operator==(EntityKind entityKind);
	bool operator!=(EntityKind entityKind);
	bool operator==(BaseKind baseKind);
	bool operator!=(BaseKind baseKind);
protected:
	
	sf::Texture mTexture;

	sf::Vector2f mPosition;
	float mHeight;
	float mWidth;

	EntityKind mEntityKind;
	BaseKind mBaseKind;
	Layer mLayer;

	bool mAlive;
	sf::Sprite mSprite;
};

#endif