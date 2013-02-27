#ifndef	INCLUDED_LEVELMANAGER
#define	INCLUDED_LEVELMANAGER
#include <string>
#include <vector>
#include "Entity.h"

struct Level 
{
	Level(std::string blockMap, std::string objectMap, std::string XmlMap, 
		 int MapRight = 61, int MapBottom = 28, Entity::EntityKind entityKind = Entity::KIBA)
	{
		mblockMap = blockMap;
		mobjectMap = objectMap;
		mXmlMap = XmlMap;

		mPrimaryCharacter = entityKind;

		mMapBottom = MapBottom;
		mMapRight = MapRight;
	}
	std::string mblockMap;
	std::string mobjectMap;
	std::string mXmlMap;

	Entity::EntityKind mPrimaryCharacter;

	int mMapBottom;
	int mMapRight;
};

class LevelManager
{
static int currentLevel;
public:
	
	typedef std::vector<Level> Levelvector;

	~LevelManager();

	void LoadLevel(int level = currentLevel);
	void LoadEndLevel();

	static LevelManager* getInstance();

	int getCurrentLevel();


private:
	typedef std::vector<std::string> StringVector;

	LevelManager();
	LevelManager(const LevelManager&);
	
	void operator=(const LevelManager&);
	static LevelManager *sInstance;

	Levelvector mLevels;

	void generateLevels();
	void generateDialogues();
	
	StringVector mStartDialogues;
	StringVector mEndDialogues;
};

#endif