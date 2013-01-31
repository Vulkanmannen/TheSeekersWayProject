#ifndef INCLUDED_ENTITYMANAGER
#define INCLUDED_ENTITYMANAGER

#include <vector>
#include "SFML\Graphics.hpp"
#include "Entity.h"

class Block;
class Character;

class EntityManager
{
public:
	typedef std::vector<Entity*> EntityVector;
	typedef std::vector<Character*> CharacterVector;

	static EntityManager* getInstance();

	~EntityManager();

	void update();
	void render();

	void addEntity(Entity *e);
	void addCharacter(Character *c, int placeInVector);

	void updatePrimaryCharacter();
	sf::Vector2f getCharacterPos()const;

private:
	EntityManager();
	EntityManager(const EntityManager &e);
	void operator=(const EntityManager &e);

	static EntityManager *sInstance;

	void checkCollisions();
	bool isColliding(Character *c, Entity *e);
	void stopEntity(Character *c, Entity *e);
	void killEntity();

	Entity::EntityKind mPrimaryCharacter;

	EntityVector mEntities;
	Character* mCharacters[4];
};

#endif 