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
	EntityManager::getInstance()->ClearAll();
	MapGenerator::generateMap(mLevels[level].mblockMap, mLevels[level].mobjectMap, mLevels[level].mXmlMap);
	currentLevel = level;

	Dialogue::getInstance()->startDialogue(mStartDialogues[level]);
	Dialogue::getInstance()->setStartDialogue(true);

	EntityManager::getInstance()->setPrimaryCharacter(mLevels[level].mPrimaryCharacter);

	EntityManager::getInstance()->setMapSize(mLevels[level].mMapRight, mLevels[level].mMapBottom);
	
	Sounds::getInstance()->StopAll();
	Sounds::getInstance()->setMasterVolume(100);
	Sounds::getInstance()->Loop("Level1Music.wav", 10);

	EntityManager::getInstance()->setPlayerLifeMax();
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
	mLevels.push_back(Level("Level1.png", "Level1Object.png", "Level1Xml.xml"));
	mLevels.push_back(Level("Level2.png", "Level2Object.png", "Level2Xml.xml", 61, 28, Entity::FENRIR));	
	mLevels.push_back(Level("Level3.png", "Level3Object.png", "Level3Xml.xml"));
	mLevels.push_back(Level("Level4.png", "Level4Object.png", "Level4Xml.xml"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png", "Level5Xml.xml", 76, 34));
	mLevels.push_back(Level("Level6.png", "Level6Object.png", "Level6Xml.xml", 73, 34));
}

void LevelManager::generateDialogues()
{
<<<<<<< HEAD
	mStartDialogues.push_back("Level1StartDialogue");
	mStartDialogues.push_back("Level2StartDialogue");
	mStartDialogues.push_back("Level3StartDialogue");
	mStartDialogues.push_back("Level4StartDialogue");
	mStartDialogues.push_back("Level5StartDialogue");

	mEndDialogues.push_back("Level1EndDialogue");
	mEndDialogues.push_back("Level2EndDialogue");
	mEndDialogues.push_back("Level3EndDialogue");
	mEndDialogues.push_back("Level4EndDialogue");
	mEndDialogues.push_back("Level5EndDialogue");
=======
	mStartDialogues.push_back("Level1StartDialogue.txt");
	mStartDialogues.push_back("Level2StartDialogue.txt");
	mStartDialogues.push_back("Level3StartDialogue.txt");
	mStartDialogues.push_back("Level4StartDialogue.txt");
	mStartDialogues.push_back("Level5StartDialogue.txt");
	//mStartDialogues.push_back("Level6StartDialogue.txt");

	mEndDialogues.push_back("Level1EndDialogue.txt");
	mEndDialogues.push_back("Level2EndDialogue.txt");
	mEndDialogues.push_back("Level3EndDialogue.txt");
	mEndDialogues.push_back("Level4EndDialogue.txt");
	mEndDialogues.push_back("Level5EndDialogue.txt");
	//mEndDialogues.push_back("Level6EndDialogue.txt");
>>>>>>> origin/master
}

int LevelManager::getCurrentLevel()
{
	return currentLevel;
}

