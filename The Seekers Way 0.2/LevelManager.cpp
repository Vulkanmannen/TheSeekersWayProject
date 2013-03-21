#include "LevelManager.h"
#include "EntityManager.h"
#include <string>
#include "MapGenerator.h"
#include "Sounds.h"
#include "Dialogue.h"

LevelManager* LevelManager::sInstance = 0;

int LevelManager::currentLevel = 0;

LevelManager::LevelManager()
{
	generateLevels();
	generateDialogues();
}


LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel(int level)
{
	if(mLevels.size() > level)
	{
		EntityManager::getInstance()->ClearAll();
		MapGenerator::generateMap(mLevels[level].mblockMap, mLevels[level].mobjectMap, mLevels[level].mXmlMap);

		currentLevel = level;

		//Sounds::getInstance()->StopAll();
		//Sounds::getInstance()->setMasterVolume(100);
		//if(level < 2)
		//{
		//	Sounds::getInstance()->Loop(mLevels[level].mMusic, 100);
		//}
		//else
		//{
		//	Sounds::getInstance()->Loop(mLevels[level].mMusic, 50);
		//}
		Dialogue::getInstance()->startDialogue(mStartDialogues[level]);
		Dialogue::getInstance()->setStartDialogue(true);

		EntityManager::getInstance()->setPrimaryCharacter(mLevels[level].mPrimaryCharacter);

		EntityManager::getInstance()->setMapSize(mLevels[level].mMapRight, mLevels[level].mMapBottom);
		EntityManager::getInstance()->setCameraSpeedToChangePos();
		

		EntityManager::getInstance()->setPlayerLifeMax();
		EntityManager::getInstance()->setCameraToPrimaryCharacer();
	}
	else
	{
		currentLevel = 0;
	}
}

void LevelManager::LoadEndLevel()
{
	Dialogue::getInstance()->startDialogue(mEndDialogues[currentLevel]);
}

LevelManager* LevelManager::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new LevelManager(); 
	}
	return sInstance;
}

void LevelManager::generateLevels()
{
	mLevels.push_back(Level("Level1.png", "Level1Object.png", "Level1Xml.xml", "Level1Music.ogg"));
	mLevels.push_back(Level("Level2.png", "Level2Object.png", "Level2Xml.xml", "Level1Music.ogg", 61, 28, Entity::FENRIR));	
	mLevels.push_back(Level("Level3.png", "Level3Object.png", "Level3Xml.xml", "Level2Music.ogg"));
	mLevels.push_back(Level("Level4.png", "Level4Object.png", "Level4Xml.xml", "Level2Music.ogg"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png", "Level5Xml.xml", "Level2Music.ogg"));
	mLevels.push_back(Level("Level6.png", "Level6Object.png", "Level6Xml.xml", "Level2Music.ogg", 76, 34));
	mLevels.push_back(Level("Level7.png", "Level7Object.png", "Level7Xml.xml", "Level2Music.ogg", 73, 34));
}

void LevelManager::generateDialogues()
{
	mStartDialogues.push_back("Level1StartDialogue");
	mStartDialogues.push_back("Level2StartDialogue");
	mStartDialogues.push_back("Level3StartDialogue");
	mStartDialogues.push_back("Level4StartDialogue");
	mStartDialogues.push_back("Level5StartDialogue");
	mStartDialogues.push_back("Level6StartDialogue");
	mStartDialogues.push_back("Level7StartDialogue");

	mEndDialogues.push_back("Level1EndDialogue");
	mEndDialogues.push_back("Level2EndDialogue");
	mEndDialogues.push_back("Level3EndDialogue");
	mEndDialogues.push_back("Level4EndDialogue");
	mEndDialogues.push_back("Level5EndDialogue");
	mEndDialogues.push_back("Level6EndDialogue");
	mEndDialogues.push_back("Level7EndDialogue");
}

int LevelManager::getCurrentLevel()
{
	return currentLevel;
}


void LevelManager::setCurrentLevel(int level)
{
	currentLevel = level;
}

std::string LevelManager::getMusic()const
{
	return mLevels[currentLevel].mMusic;
}



