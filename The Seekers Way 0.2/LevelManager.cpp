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
	Sounds::getInstance()->Loop("Level1Music.wav", 30);
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
<<<<<<< HEAD
	mLevels.push_back(Level("Level2.png", "Level2Object.png", "Level2Xml.xml", 61, 28, Entity::FENRIR));
	mLevels.push_back(Level("Level1.png", "Level1Object.png", "Level1Xml.xml"));
	
	mLevels.push_back(Level("Level3.png", "Level3Object.png", "Level3Xml.xml"));
	mLevels.push_back(Level("Level4.png", "Level4Object.png", "Level4Xml.xml", 73, 34));
	mLevels.push_back(Level("Level5.png", "Level5Object.png", "Level5Xml.xml"));
=======
	mLevels.push_back(Level("Level1.png", "Level1Object.png", "Level1Xml.xml"));
	mLevels.push_back(Level("Level2.png", "Level2Object.png", "Level2Xml.xml", 61, 28, Entity::FENRIR));
	mLevels.push_back(Level("Level3.png", "Level3Object.png", "Level3Xml.xml"));
	mLevels.push_back(Level("Level4.png", "Level4Object.png", "Level4Xml.xml", 73, 34));
	mLevels.push_back(Level("Level5.png", "Level5Object.png", "Level5Xml.xml"));

>>>>>>> origin/vulkanmannen
}

void LevelManager::generateDialogues()
{
	mStartDialogues.push_back("Level1StartDialogue.txt");
	mStartDialogues.push_back("Level2StartDialogue.txt");
	mStartDialogues.push_back("Level3StartDialogue.txt");
	mStartDialogues.push_back("Level4StartDialogue.txt");
	mStartDialogues.push_back("Level5StartDialogue.txt");

	mEndDialogues.push_back("Level1EndDialogue.txt");
	mEndDialogues.push_back("Level2EndDialogue.txt");
	mEndDialogues.push_back("Level3EndDialogue.txt");
	mEndDialogues.push_back("Level4EndDialogue.txt");
	mEndDialogues.push_back("Level5EndDialogue.txt");
}

int LevelManager::getCurrentLevel()
{
	return currentLevel;
}

