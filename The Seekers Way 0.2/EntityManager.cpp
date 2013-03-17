#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include "State.h"
#include "Character.h"
#include "Door.h"
#include "ImageManager.h"
#include "LevelManager.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Sounds.h"
#include <cmath>
#include <algorithm>
#include "MyLightSystem.h"

#include <LTBL\Light\Light_Point.h>
#include <LTBL\Constructs\Vec2f.h>
#include <LTBL\Utils.h>

EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mMaxPlayerLife(5),
	mPlayerLife(mMaxPlayerLife),
	mZeroPlayerLife(0),
	mMapTop(360),
	mMapLeft(512),
	shadeAll(false),
	mCameraLastPos(0, 0),
	mCameraSpeed(3),
	mBackgroundPos(-1024, -1024),
	mParalax(false),
	mMovingCamera(false),
	mCantMoveCharacters(false)
{		
		emote[0] = 0;
		emote[1] = 0;
		emote[2] = 0;
		emote[3] = 0;
		frame[0] = Animation("frame.png", 60, 1, 84, 84);
		frame[1] = Animation("frame.png", 60, 1, 84, 84);
		frame[2] = Animation("frame.png", 60, 1, 84, 84);
		frame[3] = Animation("frame.png", 60, 1, 84, 84);
		mPortraitSprite[0] = Animation("Kiba portraites spritesheet.png",	60, 1, 64, 64);
		mPortraitSprite[1] = Animation("charlotteportrait.png",				60, 1, 64, 64);
		mPortraitSprite[2] = Animation("Fenrir Face sprite 1_1.png",		60, 1, 64, 64);
		mPortraitSprite[3] = Animation("Sheeka Face sprite 1_1.png",		60, 1, 64, 64);
		
		shadow.loadFromFile("greyscale.frag", sf::Shader::Fragment);
		shadow.setParameter("texture", sf::Shader::CurrentTexture);
		
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);
		mDeathTexture.loadFromImage(*ImageManager::getImage("DieScreen.png"));
		mDeathSprite.setTexture(mDeathTexture);
		mMaskTexture.loadFromImage(*ImageManager::getImage("mask.png"));
		mMaskSprite.setTexture(mMaskTexture);
		mBackgroundTexture.loadFromImage(*ImageManager::getImage("background.png"));
		createBackground();
		setMapSize(61, 28);


		//mLightSystem = MyLightSystem::getLightSystem();
		//
		//mLight = new ltbl::Light_Point(); 
		//mLight->m_intensity = 100.0f; 
		//mLight->m_radius = 400.0f; 
		//mLight->m_size = 700.0f; 
		//mLight->m_spreadAngle = ltbl::pifTimes2; 
		//mLight->m_softSpreadAngle = 0.0f;
		//mLight->CalculateAABB();
		//mLight->m_color.r = 0.5f; 
		//mLight->m_color.g = 0.5f; 
		//mLight->m_color.b = 0.5f;
		//mLight->m_bleed = 1.0f; 
		//mLight->m_linearizeFactor = 2.0f; 

		//mLightSystem->AddLight(mLight); 
		//mLight->SetAlwaysUpdate(true); 

}


EntityManager::~EntityManager()
{
	for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
	{
		delete mEntities[j];
	}
}

// returnerar den enda instancen av managern
EntityManager* EntityManager::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new EntityManager;
	}
	return sInstance;
}


// uppdaterar alla objekt
void EntityManager::update()
{
	if(mPlayerLife > 0)
	{
		for(EntityVector::size_type i = 0; i < mCharacters.size(); ++i)
		{
			if(!mCantMoveCharacters)
			{
				mCharacters[i]->update(mPrimaryCharacter);
			}
			else
			{
				Entity::EntityKind noCharacter = Entity::DOOR;
				mCharacters[i]->update(noCharacter);	
			}
		}

		for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
		{
			if(mEntities[i]->getBaseKind() != Entity::CHARACTER)
			{
				mEntities[i]->update(mPrimaryCharacter);
			}
		}	

		updatePlayerLife();
		interact();
		killEntity();

		updatePlayerLife();
		lifeAndMaskPosition();

		updatePlayerPortrait();
		updateBackgroundParalax();
	}
	
	killPlayers();

	
}

// uppdaterar lifeposition
void EntityManager::lifeAndMaskPosition()
{
	mLifeSprite.setPosition(mView->getCenter() - sf::Vector2f(512, 360));

	mMaskSprite.setPosition(mView->getCenter() - sf::Vector2f(1024, 720));
}

void EntityManager::killPlayers()
{
	if(mPlayerLife <= 0)
	{
		ImageManager::render(&mDeathSprite);
		mDeathSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			LevelManager::getInstance()->LoadLevel();
			State::getInstance()->setState(State::GameState);
			mPlayerLife = mMaxPlayerLife;
		}
	}
}

// uppdaterar hur mycket liv spelaren har
void EntityManager::updatePlayerLife()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		if(mCharacters[i]->getIsHit())
		{
			mCharacters[i]->setIsHitToFalse();
			mPlayerLife--;
		}
	}
}

// uppdaterar Portraiten spelaren har
void EntityManager::updatePlayerPortrait()
{
	mPortraitSprite[0].update(emote[0]);
	mPortraitSprite[1].update(emote[1]);
	mPortraitSprite[2].update(emote[2]);
	mPortraitSprite[3].update(emote[3]);
}

void EntityManager::setEmotion(int a, int b)
{
	emote[a] = b;
	mPortraitSprite[a].update(emote[a]);
}

// ritarut alla objekt
void EntityManager::render()
{

	//mLight->SetCenter(Vec2f(mCharacters[mPrimaryCharacter]->getPosition().x, mVideoMode->height - mCharacters[mPrimaryCharacter]->getPosition().y));

	renderBackground();
	updateView();
	
	for(int h = 0; h < 4; ++h)
	{
		for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
		{
			if(mEntities[i]->getLayer() == h)
			{
				sf::Vector2f pos = mEntities[i]->getPosition();
				float width = mEntities[i]->getWidth(), height = mEntities[i]->getHeight();
				float screenWidth = mView->getSize().x + width, screenHeight = mView->getSize().y + height;
				pos.x -= (mView->getCenter().x - mView->getSize().x/2);
				pos.y -= (mView->getCenter().y - mView->getSize().y/2);
				if	( (pos.x + width) > 0 
					&& pos.x < screenWidth
					&& pos.y + height > 0
					&& pos.y < screenHeight)
				{
					mEntities[i]->render();
				}
			}
		}
	}

	renderLifeAndMask();
	renderPortrait();
	lifeAndMaskPosition();
	updateMovingCamera();
	//sf::RectangleShape rect(sf::Vector2f(mMapRight - 512, mMapBottom - 360));
	//rect.setPosition(mMapLeft, mMapTop);
	//sf::Color colo(255,255,255,128);
	//rect.setFillColor(colo);
	//ImageManager::render(&rect);

	//// Calculate the lights 
	//mLightSystem->RenderLights(); 
	//// Draw the lights 
	//mLightSystem->RenderLightTexture();

}

// renderar livet
void EntityManager::renderLifeAndMask()
{
	ImageManager::render(&mMaskSprite);
	mLifeSprite.setPosition(mLifeSprite.getPosition() + sf::Vector2f(20, frame[0].getSprite().getLocalBounds().height + 10));
	for(int i = 0; i < mPlayerLife; ++i)
	{
		ImageManager::render(&mLifeSprite);
		mLifeSprite.setPosition(mLifeSprite.getPosition() + sf::Vector2f(50, 0));
	}
}

// renderar portraitet
void EntityManager::renderPortrait()
{

	for(int i = 0; i < 4; i++)
	{
		frame[i].setPosition(	mPortraitSprite[i].getSprite().getPosition() - sf::Vector2f(9 , 9));
		sf::RenderStates states;
		states.shader = &shadow;
		frame[i].update(i);
		for(CharacterVector::size_type j = 0; j < mCharacters.size(); j++)
		{
			//totte �r kass
			switch(i)
			{
			case 0:
				if (mCharacters[j]->getEntityKind() == Entity::KIBA) 
				{
					ImageManager::render(&mPortraitSprite[0].getSprite(),	mPrimaryCharacter != Entity::KIBA || shadeAll? states : sf::RenderStates::Default);
				}
					ImageManager::render(&frame[i].getSprite(),				mPrimaryCharacter != Entity::KIBA || shadeAll? states : sf::RenderStates::Default);
				break;
			case 1:
				if (mCharacters[j]->getEntityKind() == Entity::CHARLOTTE) 
				{
					ImageManager::render(&mPortraitSprite[1].getSprite(),	mPrimaryCharacter != Entity::CHARLOTTE || shadeAll? states : sf::RenderStates::Default);
				}
					ImageManager::render(&frame[i].getSprite(),				mPrimaryCharacter != Entity::CHARLOTTE || shadeAll? states : sf::RenderStates::Default);
				break;
			case 2:
				if (mCharacters[j]->getEntityKind() == Entity::FENRIR)
				{
					ImageManager::render(&mPortraitSprite[2].getSprite(),	mPrimaryCharacter != Entity::FENRIR || shadeAll? states : sf::RenderStates::Default);
				}
					ImageManager::render(&frame[i].getSprite(),				mPrimaryCharacter != Entity::FENRIR || shadeAll? states : sf::RenderStates::Default);
				break;
			case 3:
				if (mCharacters[j]->getEntityKind() == Entity::SHEEKA) 
				{
					ImageManager::render(&mPortraitSprite[3].getSprite(),	mPrimaryCharacter != Entity::SHEEKA || shadeAll? states : sf::RenderStates::Default);
				}
					ImageManager::render(&frame[i].getSprite(),				mPrimaryCharacter != Entity::SHEEKA || shadeAll? states : sf::RenderStates::Default);
				break;
			}
		}
		mPortraitSprite[i].setPosition(	mView->getCenter() - sf::Vector2f(503 - i * frame[i].getSprite().getLocalBounds().width, 351));
	}
	
}

// tilar bakgrunden
void EntityManager::createBackground()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 12; ++j)
		{
			sf::Sprite background;
			background.setTexture(mBackgroundTexture);
			background.setPosition(sf::Vector2f(i *512, j * 512) + mBackgroundPos);
			mBackgroundSprites.push_back(background);
		}
	}
}

// renderar bakgrunden
void EntityManager::renderBackground()
{
	for(std::vector<sf::Sprite>::size_type i = 0; i < mBackgroundSprites.size(); ++i)
	{
		ImageManager::render(&mBackgroundSprites[i]);
	}
}

void EntityManager::updateMovingCamera()
{
	updateBackgroundPos();

	sf::Vector2f cameraPos = mView->getCenter();

	sf::Vector2f dist = cameraPos - mCameraLastPos;
	
	if(dist.x == 0 && dist.y == 0 || (mParalaxClock.getElapsedTime().asMilliseconds() > 50 && !mCantMoveCharacters))
	{
		mMovingCamera = false;
	}

	if(dist.x < 0.0001, dist.y < 0.0001)
	{
		mParalaxClock.restart();
		mCantMoveCharacters = false;
	}

	mCameraLastPos = mView->getCenter();
}
void EntityManager::updateBackgroundParalax()
{
	sf::Vector2f cameraPos = mView->getCenter();

	sf::Vector2f dist = cameraPos - mCameraLastPos;

	if(mParalax && !mMovingCamera)
	{
		mBackgroundPos += sf::Vector2f(dist.x * 0.1, dist.y * 0.1);
	}

	mCameraLastPos = mView->getCenter();
}

void EntityManager::updateBackgroundPos()
{
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 12; ++j)
		{
			mBackgroundSprites[i * 12 + j].setPosition(sf::Vector2f(i *512, j * 512) + mBackgroundPos);	
		}
	}
}

// l�gger till en entiteter i de vectorer de ska va i.
void EntityManager::addEntity(Entity *e)
{
	mEntities.push_back(e);

	switch(e->getEntityKind())
	{
	case Entity::ARROW:
	case Entity::SHIELD:
	case Entity::DARKBINDING:
	case Entity::STONE:
	case Entity::SPIKETRAP:
	case Entity::SLASH:
	case Entity::WOODENWALL:
		mDynamicEntities.push_back(e);
		break;
	}

	if(e->getBaseKind() == Entity::CHARACTER)
	{
		mDynamicEntities.push_back(e);
		mCharacters.push_back(static_cast<Character*>(e));
	}
}

// kollar om en karakt�r kolliderar
bool EntityManager::isColliding(Entity *c, Entity *e)
{
	if(c->getTop() > e->getBottom())
	{
		return false;
	}
	else if(c->getBottom() < e->getTop())
	{
		return false;
	}
	else if(c->getRight() < e->getLeft())
	{
		return false;
	}
	else if(c->getLeft() > e->getRight())
	{
		return false;
	}
	else
	{
		return true;
	}
}

// tar bort entiterter som �r d�da i b�de entityvectorn och dynamicentityvektorn
void EntityManager::killEntity()
{
	for(EntityVector::size_type i = 0; i < mDynamicEntities.size(); ++i)
	{
		if(mDynamicEntities[i]->getAliveStatus() == false)
		{
			for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
			{
				if(mDynamicEntities[i] == mEntities[j])
				{
					mEntities[j] = mEntities.back();
					mEntities.pop_back();
				}
			}
			delete mDynamicEntities[i];
			mDynamicEntities[i] = mDynamicEntities.back();
			mDynamicEntities.pop_back();
		}	
	}
}

// uppdaterar vilken som �r den prim�ra karakt�ren
void EntityManager::updatePrimaryCharacter()
{
	Entity::EntityKind tempEntityKind = mPrimaryCharacter;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		tempEntityKind = Entity::KIBA;
		setCameraSpeedToChangePos();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		tempEntityKind = Entity::CHARLOTTE;
		setCameraSpeedToChangePos();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		tempEntityKind = Entity::FENRIR;
		setCameraSpeedToChangePos();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		tempEntityKind = Entity::SHEEKA;
		setCameraSpeedToChangePos();
	}

	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i) // kollar om den valda karakt�ren finns i vektorn
	{
		if(mCharacters[i]->getEntityKind() == tempEntityKind)
		{
			if(tempEntityKind != mPrimaryCharacter)
			{
				Sounds::getInstance()->Play("switch char 1.1.wav", 6);
				mPrimaryCharacter = tempEntityKind;
			}
		}
	}
}

// returnerar positionen till den prim�ra karakt�ren
sf::Vector2f EntityManager::getCharacterPos()const
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		if(mCharacters[i]->getEntityKind() == mPrimaryCharacter)
		{
			return mCharacters[i]->getPosition();
		}
	}
}

// s�tter primarycharacter
void EntityManager::setPrimaryCharacter(Entity::EntityKind entityKind)
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i) // kollar om den valda karakt�ren finns i vektorn
	{
		if(mCharacters[i]->getEntityKind() == entityKind)
		{
			mPrimaryCharacter = entityKind;
			return;
		}
	}

	if(mCharacters.size() > 0)
	{
		mPrimaryCharacter = mCharacters[0]->getEntityKind();
	}
}

void EntityManager::interact()
{
	//k�r interact mot alla som krockar
	for(EntityVector::size_type i = 0; i < mDynamicEntities.size(); ++i)
	{
		for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
		{
			if(mDynamicEntities[i] != mEntities[j])
			{
				if(mDynamicEntities[i]->getAliveStatus() && mEntities[j]->getAliveStatus())
				{
					if(isColliding(mDynamicEntities[i], mEntities[j]))
					{
						mDynamicEntities[i]->interact(mEntities[j]);
						mEntities[j]->interact(mDynamicEntities[i]);
					}
				}
			}
		}
	}
}

// s�tter viewn
void EntityManager::setView(sf::View* view, sf::VideoMode* videoMode)
{
	mView = view;
	mVideoMode = videoMode;
	mCameraLastPos = view->getCenter();
}

sf::View* EntityManager::getView()
{
	return mView;
}

// updaterar view positionen
void EntityManager::updateView()
{
	sf::Vector2f playerPos = getCharacterPos();

	sf::Vector2f dist = playerPos - mView->getCenter();

	float length = 0;
	length = std::sqrt((dist.x * dist.x) + (dist.y *dist.y));
	
	if(dist != sf::Vector2f(0, 0))
	{
		
		dist.x *= 1.0f / length;
		dist.y *= 1.0f / length;
	}	

	if(length > 5)
	{
		if(length < 100)
		{
			if(length > 20)
			{
				mCameraSpeed = 7;
			}
			else
			{
				mCameraSpeed = 3;	
				mParalax = true;
			}	
			
		}
		mView->setCenter(mView->getCenter() + sf::Vector2f(dist.x * mCameraSpeed, dist.y * mCameraSpeed));
	}
	else
	{
		mView->setCenter(playerPos);
	}
	
	if(mView->getCenter().x < mMapLeft)
	{
		mView->setCenter(sf::Vector2f(mMapLeft, mView->getCenter().y));
		mParalax = true;
	}
	else if(mView->getCenter().x > mMapRight)
	{
		mView->setCenter(sf::Vector2f(mMapRight, mView->getCenter().y));
		mParalax = true;
	}
	if(mView->getCenter().y < mMapTop)
	{
		mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapTop));
		mParalax = true;
	}
	else if(mView->getCenter().y > mMapBottom)
	{
		mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapBottom));
		mParalax = true;
	}

	//if(playerPos.x > mMapLeft && playerPos.x < mMapRight)
	//{
	//	mView->setCenter(sf::Vector2f(playerPos.x, mView->getCenter().y));
	//}
	//else
	//{
	//	if(playerPos.x > mMapRight / 2)
	//	{
	//		mView->setCenter(sf::Vector2f(mMapRight, mView->getCenter().y));
	//	}
	//	else
	//	{
	//		mView->setCenter(sf::Vector2f(mMapLeft, mView->getCenter().y));
	//	}	
	//}
	//// det st�r fan totte �verallt
	//// jag vet!!! och det st�r mig som faaan!
	//if(playerPos.y > mMapTop && playerPos.y < mMapBottom)
	//{
	//	mView->setCenter(sf::Vector2f(mView->getCenter().x, playerPos.y));
	//}
	//else
	//{
	//	if(playerPos.y > mMapBottom / 2)
	//	{
	//		mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapBottom));
	//	}
	//	else
	//	{
	//		mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapTop));
	//	}
	//}
	
}

// s�tter storleken p� mappen tar emot fyra inter, l�ng o h�jd r�knat i block samt antalet bakgrunder i h�jdled och l�ngd;
void EntityManager::setMapSize(int numberOfBlocksRight, int numberOfBlocksBottom)
{
	mMapRight = numberOfBlocksRight * 64 - 576;
	mMapBottom = numberOfBlocksBottom * 64 - 424;
}

// returnerar storleken p� mCharacters
int EntityManager::getSizeOfCharacterVector()const
{
	return static_cast<int>(mCharacters.size());
}

void EntityManager::ClearAll()
{
	while(!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
	mDynamicEntities.clear();
	mCharacters.clear();

	mBackgroundPos = sf::Vector2f(-1024, -1024);
}

void EntityManager::setPlayerLifeMax()
{
	mPlayerLife = mMaxPlayerLife;
}

void EntityManager::setPlayerLifeZero()
{
	mPlayerLife = mZeroPlayerLife;
}

void EntityManager::setShadeAll(bool a)
{
	shadeAll = a;
}

void EntityManager::SetAniToIdle()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); i++)
	{
		mCharacters[i]->setStatusIdle();
	}
}

void EntityManager::setCameraSpeedToChangePos()
{
	mCameraSpeed = 25;
	mParalax = false;
	mMovingCamera = true;
	mCantMoveCharacters = true;
}

sf::Vector2f EntityManager::getBackgroundPos()const
{
	return mBackgroundPos;
}

void EntityManager::updateCameraLastpos()
{
	mCameraLastPos = mView->getCenter();
}

bool EntityManager::getMovingCamera()const
{
	return mMovingCamera;
}