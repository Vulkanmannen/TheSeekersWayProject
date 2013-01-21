#ifndef INCLUDED_ENTITYMANAGER
#define INCLUDED_ENTITYMANAGER

#include <vector>

class Entity;
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

private:
	EntityManager();
	EntityManager(const EntityManager &e);
	void operator=(const EntityManager &e);

	static EntityManager *sInstance;

	void checkCollisions();
	bool isColliding(Character *c, Entity *e);
	void stopEntity(Character *c, Entity *e);

	EntityVector mEntities;
	CharacterVector mCharacters;
};

#endif 