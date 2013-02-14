#ifndef INCLUDED_ENTITYMANAGER
#define INCLUDED_ENTITYMANAGER

#include <vector>
#include "SFML\Graphics.hpp"
#include "Entity.h"
#include <vector>

class Block;
class Character;

class EntityManager
{
public:
	typedef std::vector<Entity*> EntityVector;
	typedef std::vector<Entity*> DynamicEntityVector;
	typedef std::vector<Character*> CharacterVector;

	static EntityManager* getInstance();

	~EntityManager();

	void update();
	void render();

	void addEntity(Entity *e);

	void updatePrimaryCharacter();
	sf::Vector2f getCharacterPos()const;

	void setView(sf::View* view);

private:
	EntityManager();
	EntityManager(const EntityManager &e);
	void operator=(const EntityManager &e);

	static EntityManager *sInstance;

	void interact();

	bool isColliding(Entity *c, Entity *e);

	void killEntity();

	Entity::EntityKind mPrimaryCharacter;

	EntityVector		mEntities;
	DynamicEntityVector mDynamicEntities;
	CharacterVector		mCharacters;
	
	sf::View* mView;
	
	//--------------life
	int mPlayerLife;
	sf::Texture mLifeTexture;
	sf::Sprite mLifeSprite;
	void updateLife();

	//---------- mask
	sf::Texture mMaskTexture;
	sf::Sprite mMaskSprite;

	void renderLifeAndMask();
	void lifeAndMaskPosition();

	// ----------------- background
	sf::Texture mBackgroundTexture;
	std::vector<sf::Sprite> mBackgroundSprites;

	void createBackground();
	void renderBackground();
};

#endif 