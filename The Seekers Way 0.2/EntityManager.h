#ifndef INCLUDED_ENTITYMANAGER
#define INCLUDED_ENTITYMANAGER

#include <vector>
#include "SFML\Graphics.hpp"
#include "Entity.h"
#include "Animation.h"
#include <vector>

#include <LTBL\Light\Light_Point.h>
#include <LTBL\Light\LightSystem.h>

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

	void setPlayerLifeZero();
	void setPlayerLifeMax();
	void ClearAll();
	void addEntity(Entity *e);

	void updatePrimaryCharacter();
	sf::Vector2f getCharacterPos()const;
	void setPrimaryCharacter(Entity::EntityKind);

	void setView(sf::View* view, sf::VideoMode* videoMode);
	sf::View* getView();
	void updateView();
	
	void setMapSize(int numberOfBlocksWidth, int numberOfBlocksHeight);
	void setEmotion(int character, int emotion);
	void setShadeAll(bool);

	int getSizeOfCharacterVector()const;

	//------------FinishDoor Animations on Char
	void SetAniToIdle();

	void setCameraSpeedToChangePos();

private:
	EntityManager();
	EntityManager(const EntityManager &e);
	void operator=(const EntityManager &e);

	static EntityManager *sInstance;

	void interact();

	bool isColliding(Entity *c, Entity *e);

	void killEntity();

	Entity::EntityKind mPrimaryCharacter;
	sf::Vector2f mCharacterLastPos;

	EntityVector		mEntities;
	DynamicEntityVector mDynamicEntities;
	CharacterVector		mCharacters;
	
	sf::View* mView;
	sf::VideoMode* mVideoMode;
	
	//--------------life
	int mZeroPlayerLife;
	int mMaxPlayerLife;
	int mPlayerLife;
	sf::Texture mDeathTexture;
	sf::Sprite mDeathSprite;
	sf::Texture mLifeTexture;
	sf::Sprite mLifeSprite;
	void updatePlayerLife();
	void killPlayers();

	//---------- mask
	sf::Texture mMaskTexture;
	sf::Sprite mMaskSprite;
	float mCameraSpeed;

	void renderLifeAndMask();
	void lifeAndMaskPosition();

	//--------------portrait
	Animation mPortraitSprite[4];
	void renderPortrait();
	void updatePlayerPortrait();

	int emote[4];
	Animation frame[4];
	sf::Shader shadow;
	bool shadeAll;
	// ----------------- background
	sf::Texture mBackgroundTexture;
	std::vector<sf::Sprite> mBackgroundSprites;

	void createBackground();
	void renderBackground();
	
	//------------mapsize
	int mMapRight;
	int mMapLeft;
	int mMapTop;
	int mMapBottom;

	//------------light
	ltbl::Light_Point* mLight;
	ltbl::LightSystem* mLightSystem;
};

#endif 