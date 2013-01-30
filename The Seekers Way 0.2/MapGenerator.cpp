#include "MapGenerator.h"
#include "EntityManager.h"
#include "NormalBlock.h"
#include "Kiba.h"
#include "Fenrir.h"
#include "GenerateDoor.h"
#include "Sheeka.h"
#include "Charlotte.h"

MapGenerator::MapGenerator()
	{}


MapGenerator::~MapGenerator()
	{}

void MapGenerator::generateMap(std::string imageName)
{
	GenerateDoor::loadDocument("config.xml");
	GenerateDoor::GenerateDoors();

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
			else if(color == sf::Color(0, 200, 0, 255))
			{
				EntityManager::getInstance()->addCharacter(new Fenrir(position));
			}
			else if(color == sf::Color(0, 255, 0, 255))
			{
				EntityManager::getInstance()->addCharacter(new Sheeka(position));
			}
			else if(color == sf::Color(0, 0, 200, 255))
			{
				EntityManager::getInstance()->addCharacter(new Charlotte(position));
			}
		}
	}
}