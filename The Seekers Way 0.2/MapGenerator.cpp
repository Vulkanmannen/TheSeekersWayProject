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

			EntityManager* entityManager = EntityManager::getInstance();

			if(color.r == 0 && color.a == 255)
			{
				entityManager->addEntity(new NormalBlock(position, color.b));
			}

			else if(color.r == 100 && color.a == 255)
			{	
				Entity* entity; 
				
				if(color.g == 0)
				{	
					entity = new Sheeka(position);
					entityManager->addCharacter(static_cast<Character*>(entity), 0);
				}
				else if(color.g == 100)
				{
					entity = new Fenrir(position);
					entityManager->addCharacter(static_cast<Character*>(entity), 1);
				}
				else if(color.g == 200)
				{
					entity = new Charlotte(position);
					entityManager->addCharacter(static_cast<Character*>(entity), 2);
				}
				else if(color.g == 255)
				{
					entity = new Kiba(position);
					entityManager->addCharacter(static_cast<Character*>(entity), 3);
				}
				
				entityManager->addCharacter(static_cast<Character*>(entity), 1);
				entityManager->addEntity(entity);
				entityManager->addDynamicEntity(entity);
			}
		}
	}
}