#include "MapGenerator.h"
#include "EntityManager.h"
#include "NormalBlock.h"
#include "Kiba.h"
#include "Fenrir.h"
#include "GenerateDoor.h"


MapGenerator::MapGenerator()
	{}


MapGenerator::~MapGenerator()
	{}

void MapGenerator::generateMap(std::string imageName)
{
	sf::Image image;
	image.loadFromFile(imageName);

	for(int i = 0; i < image.getSize().x; ++i)
	{
		for(int j = 0; j < image.getSize().y; ++j)
		{
			sf::Color color = image.getPixel(i ,j);
			sf::Vector2f position = sf::Vector2f(i * 64.f, j *64.f);

			if(color == sf::Color(0,0,0,255))
			{
				EntityManager::getInstance()->addEntity(new NormalBlock(position));
			}
			else if(color == sf::Color(0, 0, 255, 255))
			{
				EntityManager::getInstance()->addCharacter(new Fenrir(position));
			}
		}
	}
	GenerateDoor::loadDocument("config.xml");
	GenerateDoor::GenerateDoors();
}