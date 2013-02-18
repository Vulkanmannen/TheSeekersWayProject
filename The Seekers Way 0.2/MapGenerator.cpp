#include "MapGenerator.h"
#include "EntityManager.h"
#include "NormalBlock.h"
#include "Kiba.h"
#include "Fenrir.h"
#include "GenerateDoor.h"
#include "Sheeka.h"
#include "Charlotte.h"
#include "ShottingTrap.h"
#include "SpikeBlock.h"
#include "FireBall.h"
#include "FireRune.h"
#include "Vine.h"
#include "Stone.h"
#include "Lava.h"
#include "WoodenWall.h"

MapGenerator::MapGenerator()
	{}


MapGenerator::~MapGenerator()
	{}

void MapGenerator::generateMap(std::string imageNameBlock, std::string imageNameObject)
{
	GenerateDoor::loadDocument("config.xml");
	GenerateDoor::GenerateDoors();

	sf::Image image;
	image.loadFromFile(imageNameBlock);
	EntityManager* entityManager = EntityManager::getInstance();
	//
	//------------------------------------------------------skapar block och karaktärer
	//
	for(int i = 0; i < image.getSize().x; ++i)
	{
		for(int j = 0; j < image.getSize().y; ++j)
		{
			sf::Color color = image.getPixel(i ,j);
			sf::Vector2f position = sf::Vector2f(i * 64.f, j *64.f);

			// Skapar Block vid Red = 0
			if(color.r == 0 && color.a == 255)
			{
				if(color.g == 0)
				{
					entityManager->addEntity(new NormalBlock(position, color.b));
				}
				else if(color.g == 50)
				{
					entityManager->addEntity(new FireRune(position));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new Vine(position, color.b));
				}
				else if(color.g == 150)
				{
					entityManager->addEntity(new Stone(position));
				}
				else if(color.g == 200)
				{
					entityManager->addEntity(new Lava(position));
				}
				else if(color.g == 250)
				{
					entityManager->addEntity(new WoodenWall(position));
				}
			}

			// Skapar Karaktärerna när red = 100
			else if(color.r == 100 && color.a == 255)
			{			
				if(color.g == 0)
				{	
					entityManager->addEntity(new Kiba(position));
				}
				else if(color.g == 50)
				{
					entityManager->addEntity(new Charlotte(position));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new Fenrir(position));
				}
				else if(color.g == 150)
				{
					entityManager->addEntity(new Sheeka(position));
				}
			}
		}
	}
	//
	//------------------------------------------------------------------------skapar objekt
	//

	image.loadFromFile(imageNameObject);

	for(int i = 0; i < image.getSize().x; ++i)
	{
		for(int j = 0; j < image.getSize().y; ++j)
		{
			sf::Color color = image.getPixel(i ,j);
			sf::Vector2f position = sf::Vector2f(i * 64.f, j *64.f);

			// Skapar Object vid Red = 200
			if(color.r == 200 && color.a == 255)
			{
				if(color.g == 0) // höger :-P Sista färgen avgör skut intervallet i tiondels sekunder
				{
					entityManager->addEntity(new ShottingTrap(position, color.b, true, false));
				}
				else if(color.g == 50) // vänster :-b
				{
					entityManager->addEntity(new ShottingTrap(position,color.b ,true, true));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new SpikeBlock(position));
				}
			}
		}
	}
}