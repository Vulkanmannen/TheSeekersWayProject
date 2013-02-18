#ifndef INCLUDED_ENTITYMANAGER
#define INCLUDED_ENTITYMANAGER

#include <vector>
#include "SFML\Graphics.hpp"
#include "Entity.h"
#include "Animation.h"

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
	sf::View* getView();

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

	//--------------life
	int mPlayerLife;
	sf::Texture mLifeTexture;
	sf::Sprite mLifeSprite;
	void renderLife();
	void lifePosition();
	void updatePlayerLife();
	
	//--------------portrait
	Animation mPortraitSprite[4];
	void renderPortrait();
	void updatePlayerPortrait();

	sf::Texture frameTexture;
	sf::Sprite frame;

	sf::View* mView;
};

#endif 