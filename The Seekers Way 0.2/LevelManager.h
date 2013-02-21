#ifndef	INCLUDED_LEVELMANAGER
#define	INCLUDED_LEVELMANAGER
#include <string>
#include <vector>

struct Level 
{
	Level(std::string blockMap, std::string objectMap, std::string XmlMap, 
		 int MapRight = 61, int MapBottom = 28)
	{
		mblockMap = blockMap;
		mobjectMap = objectMap;
		mXmlMap = XmlMap;
		mMapBottom = MapBottom;
		mMapRight = MapRight;
	}
	std::string mblockMap;
	std::string mobjectMap;
	std::string mXmlMap;

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
	static LevelManager* getInstance();

	int getCurrentLevel();


private:

	LevelManager();
	LevelManager(const LevelManager&);
	
	void operator=(const LevelManager&);
	static LevelManager *sInstance;

	Levelvector mLevels;

	void generateLevels();
	
	

};

#endif