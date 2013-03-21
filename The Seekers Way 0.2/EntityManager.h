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

	sf::Vector2f getBackgroundPos()const;
	bool getMovingCamera()const;
	void updateCameraLastpos();
	void setCameraToPrimaryCharacer();
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
	
	// -------------------camera
	sf::View* mView;
	sf::VideoMode* mVideoMode;
	sf::Vector2f mCameraLastPos;
	sf::Vector2f mCameraDist;
	sf::Vector2f mCameraFakePos;
	bool mMovingCamera;
	bool mCantMoveCharacters;
	sf::Clock mParalaxClock;
	void updateMovingCamera();
	

	//--------------life
	int mZeroPlayerLife;
	int mMaxPlayerLife;
	int mPlayerLife;
	sf::Texture mDeathTexture;
	sf::Sprite mDeathSprite;
	sf::Texture mLifeTexture;
	sf::Sprite mLifeSprite;
	sf::Texture mLifeFrameTexture;
	sf::Sprite mLifeFrameSprite;
	void updatePlayerLife();
	void killPlayers();
	int mFadeCount;

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
	sf::Vector2f mBackgroundPos;
	bool mParalax;

	void createBackground();
	void renderBackground();
	void updateBackgroundPos();
	void updateBackgroundParalax();
	
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