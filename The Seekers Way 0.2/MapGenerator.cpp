#include "MapGenerator.h"
#include "EntityManager.h"
#include "NormalBlock.h"
#include "Kiba.h"
#include "Fenrir.h"
#include "GenerateDoor.h"
#include "Sheeka.h"
#include "Charlotte.h"
#include "ShottingTrap.h"
#include "Spiketrap.h"

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

			EntityManager* entityManager = EntityManager::getInstance();

			if(color.r == 0 && color.a == 255)
			{
				if(color.g == 0)
				{
					entityManager->addEntity(new NormalBlock(position, color.b));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new Spiketrap(position));
				}
			}


			else if(color.r == 100 && color.a == 255)
			{			
				if(color.g == 0)
				{	
					entityManager->addEntity(new Sheeka(position));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new Fenrir(position));
				}
				else if(color.g == 200)
				{
					entityManager->addEntity(new Charlotte(position));
				}
				else if(color.g == 255)
				{
					entityManager->addEntity(new Kiba(position));
				}
			}


			else if(color.r == 200 && color.a == 255)
			{
				if(color.g == 0 && (color.b == 0 || color.b == 1))
				{
					entityManager->addEntity(new ShottingTrap(position, true, color.b));
				}
			}
		}
	}
}