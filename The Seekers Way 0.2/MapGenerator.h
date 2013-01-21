#ifndef INCLUDED_MAPGENERATOR
#define INCLUDED_MAPGENERATOR

#include <string>
#include "SFML\Graphics.hpp"

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	static void generateMap(std::string imageName);
private:
};

#endif