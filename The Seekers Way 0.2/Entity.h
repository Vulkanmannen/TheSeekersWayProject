#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "SFML\Graphics.hpp"

class Entity
{
public:
	enum EntityKind {KIBA, FENRIR, CHARLOTTE, SHEEKA, 
	NORMALBLOCK, BUTTON, DOOR, STONE, BROKENWALL, 
	SHOTTINGTRAP, WALLTRAP, WOODENWALL, IRONBARS, 
	FLOORTRAP, ARROW, SHIELD, PORTAL, REVEAL};

	enum BaseKind {CHARACTER, BLOCK, OBJECT};

	Entity();
	virtual ~Entity();
	virtual void update() = 0;

	void render();
	
	sf::Vector2f getPosition()const;
	float getTop()const;
	float getBottom()const;
	float getRight()const;
	float getLeft()const;
	float getWidth()const;
	float getHeight()const;
	EntityKind getEntityKind()const;
	BaseKind getBaseKind()const;

	bool getAliveStatus()const;

	void destroy();

	void setPosition(sf::Vector2f &v);
protected:
	sf::Sprite mSprite;
	sf::Texture mTexture;

	sf::Vector2f mPosition;
	float mHeight;
	float mWidth;

	EntityKind mEntityKind;
	BaseKind mBaseKind;

	bool mAlive;
};

#endif