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

EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mMaxPlayerLife(5),
	mPlayerLife(mMaxPlayerLife),
	mZeroPlayerLife(0),
	mMapTop(360),
	mMapLeft(512)
{		
		frame[0] = Animation("frame.png", 60, 1, 84, 84);
		frame[1] = Animation("frame.png", 60, 1, 84, 84);
		frame[2] = Animation("frame.png", 60, 1, 84, 84);
		frame[3] = Animation("frame.png", 60, 1, 84, 84);
		mPortraitSprite[0] = Animation("PortraitesKiba.png", 60, 1, 64, 64);
		mPortraitSprite[1] = Animation("PortraitesCharlotte.png", 60, 1, 64, 64);
		mPortraitSprite[2] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
		mPortraitSprite[3] = Animation("Sheeka Face sprite 1_1.png", 60, 1, 64, 64);
		shadow.loadFromFile("greyscale.frag", sf::Shader::Fragment);
		shadow.setParameter("texture", sf::Shader::CurrentTexture);
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);
		mDeathTexture.loadFromFile("DieScreen.png");
		mDeathSprite.setTexture(mDeathTexture);
		mMaskTexture.loadFromImage(*ImageManager::getImage("mask.png"));
		mMaskSprite.setTexture(mMaskTexture);
		mBackgroundTexture.loadFromImage(*ImageManager::getImage("background.png"));
		createBackground();
		setMapSize(61, 28);
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
		for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
		{
			mEntities[i]->update(mPrimaryCharacter);
		}
	

		updatePlayerLife();
		interact();
		killEntity();

		updatePlayerLife();
		lifeAndMaskPosition();

		updatePlayerPortrait();
	}
	
	killPlayers();
}

// uppdaterar lifeposition
void EntityManager::lifeAndMaskPosition()
{
	mLifeSprite.setPosition(mView->getCenter() - sf::Vector2f(512, 360));
	mMaskSprite.setPosition(getCharacterPos() - sf::Vector2f(1024, 720));
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
	mPortraitSprite[0].update(0);
	mPortraitSprite[1].update(0);
	mPortraitSprite[2].update(0);
	mPortraitSprite[3].update(0);
}

// ritarut alla objekt
void EntityManager::render()
{
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
	//sf::RectangleShape rect(sf::Vector2f(mMapRight - 512, mMapBottom - 360));
	//rect.setPosition(mMapLeft, mMapTop);
	//sf::Color colo(255,255,255,128);
	//rect.setFillColor(colo);
	//ImageManager::render(&rect);
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
			//totte är kass
			switch(i)
			{
			case 0:
				if (mCharacters[j]->getEntityKind() == Entity::KIBA) 
				{
					ImageManager::render(&mPortraitSprite[0].getSprite(), mPrimaryCharacter != Entity::KIBA ? states : sf::RenderStates::Default);
				}
				ImageManager::render(&frame[i].getSprite(), mPrimaryCharacter != Entity::KIBA ? states : sf::RenderStates::Default);
				break;
			case 1:
				if (mCharacters[j]->getEntityKind() == Entity::CHARLOTTE) 
				{
					ImageManager::render(&mPortraitSprite[1].getSprite(), mPrimaryCharacter != Entity::CHARLOTTE ? states : sf::RenderStates::Default);
				}
				ImageManager::render(&frame[i].getSprite(), mPrimaryCharacter != Entity::CHARLOTTE ? states : sf::RenderStates::Default);
				break;
			case 2:
				if (mCharacters[j]->getEntityKind() == Entity::FENRIR)
				{
					ImageManager::render(&mPortraitSprite[2].getSprite(), mPrimaryCharacter != Entity::FENRIR ? states : sf::RenderStates::Default);
				}
				ImageManager::render(&frame[i].getSprite(), mPrimaryCharacter != Entity::FENRIR ? states : sf::RenderStates::Default);
				break;
			case 3:
				if (mCharacters[j]->getEntityKind() == Entity::SHEEKA) 
				{
					ImageManager::render(&mPortraitSprite[3].getSprite(), mPrimaryCharacter != Entity::SHEEKA ? states : sf::RenderStates::Default);
				}
				ImageManager::render(&frame[i].getSprite(), mPrimaryCharacter != Entity::SHEEKA ? states : sf::RenderStates::Default);
				break;
			}
		}
		mPortraitSprite[i].setPosition(	mView->getCenter() - sf::Vector2f(503 - i * frame[i].getSprite().getLocalBounds().width, 351));
	}
	
}

// tilar bakgrunden
void EntityManager::createBackground()
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			sf::Sprite background;
			background.setTexture(mBackgroundTexture);
			background.setPosition(i *1952, j * 896);
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

// lägger till en entiteter i de vectorer de ska va i.
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

// kollar om en karaktär kolliderar
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

// tar bort entiterter som är döda i både entityvectorn och dynamicentityvektorn
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

// uppdaterar vilken som är den primära karaktären
void EntityManager::updatePrimaryCharacter()
{
	Entity::EntityKind tempEntityKind = mPrimaryCharacter;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		tempEntityKind = Entity::KIBA;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		tempEntityKind = Entity::CHARLOTTE;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		tempEntityKind = Entity::FENRIR;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		tempEntityKind = Entity::SHEEKA;
	}

	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i) // kollar om den valda karaktären finns i vektorn
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

// returnerar positionen till den primära karaktären
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

// sätter primarycharacter
void EntityManager::setPrimaryCharacter(Entity::EntityKind entityKind)
{
	mPrimaryCharacter = entityKind;
}

void EntityManager::interact()
{
	//kör interact mot alla som krockar
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

// sätter viewn
void EntityManager::setView(sf::View* view)
{
	mView = view;
}

sf::View* EntityManager::getView()
{
	return mView;
}

// updaterar view positionen
void EntityManager::updateView()
{
	sf::Vector2f playerPos = getCharacterPos();
	
	if(playerPos.x > mMapLeft && playerPos.x < mMapRight)
	{
		mView->setCenter(sf::Vector2f(playerPos.x, mView->getCenter().y));
	}
	else
	{
		if(playerPos.x > mMapRight / 2)
		{
			mView->setCenter(sf::Vector2f(mMapRight, mView->getCenter().y));
		}
		else
		{
			mView->setCenter(sf::Vector2f(mMapLeft, mView->getCenter().y));
		}	
	}
	// det står fan totte överallt
	// jag vet!!! och det stör mig som faaan!
	if(playerPos.y > mMapTop && playerPos.y < mMapBottom)
	{
		mView->setCenter(sf::Vector2f(mView->getCenter().x, playerPos.y));
	}
	else
	{
		if(playerPos.y > mMapBottom / 2)
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapBottom));
		}
		else
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapTop));
		}
	}
}

// sätter storleken på mappen tar emot fyra inter, läng o höjd räknat i block samt antalet bakgrunder i höjdled och längd;
void EntityManager::setMapSize(int numberOfBlocksRight, int numberOfBlocksBottom)
{
	mMapRight = numberOfBlocksRight * 64 - 576;
	mMapBottom = numberOfBlocksBottom * 64 - 424;
}

// returnerar storleken på mCharacters
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
}

void EntityManager::setPlayerLifeMax()
{
	mPlayerLife = mMaxPlayerLife;
}

void EntityManager::setPlayerLifeZero()
{
	mPlayerLife = mZeroPlayerLife;
}

void EntityManager::SetAniToIdle()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); i++)
	{
		mCharacters[i]->setStatusIdle();
	}
}