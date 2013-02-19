#include "LevelManager.h"
#include "EntityManager.h"
#include <string>
#include "MapGenerator.h"

LevelManager* LevelManager::sInstance = 0;

LevelManager::LevelManager()
{
	generateLevels();
}


LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel(int level)
{
	EntityManager::getInstance()->ClearAll();
	MapGenerator::generateMap(mLevels[level -1].mblockMap, mLevels[level -1].mobjectMap);
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
	mLevels.push_back(Level("Level5.png", "Level5Object.png"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png"));
	mLevels.push_back(Level("Level5.png", "Level5Object.png"));
}