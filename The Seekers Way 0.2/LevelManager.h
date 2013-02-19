#ifndef	INCLUDED_LEVELMANAGER
#define	INCLUDED_LEVELMANAGER
#include <string>
#include <vector>

struct Level 
{
	Level(std::string blockMap, std::string objectMap)
	{
		mblockMap = blockMap;
		mobjectMap = objectMap;
	}
	std::string mblockMap;
	std::string mobjectMap;
};

class LevelManager
{
public:
	
	typedef std::vector<Level> Levelvector;

	~LevelManager();

	void LoadLevel(int level);
	static LevelManager* getInstance();


private:

	LevelManager();
	LevelManager(const LevelManager&);
	
	void operator=(const LevelManager&);
	static LevelManager *sInstance;

	Levelvector mLevels;

	void generateLevels();

};

#endif