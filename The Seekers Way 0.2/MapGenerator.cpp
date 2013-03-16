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
#include "FinishDoor.h"
#include "Decoration.h"
#include "TutorialSign.h"

MapGenerator::MapGenerator()
	{}


MapGenerator::~MapGenerator()
	{}

void MapGenerator::generateMap(std::string imageNameBlock, std::string imageNameObject, std::string imageNameXML)
{
	GenerateDoor::loadDocument(imageNameXML);
	GenerateDoor::GenerateDoors();

	sf::Image image;
	image.loadFromFile("Maps/" + imageNameBlock);
	EntityManager* entityManager = EntityManager::getInstance();
	//
	//------------------------------------------------------skapar block och karakt�rer
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
				else if(color.g == 255)
				{
					entityManager->addEntity(new FinishDoor(position));
				}
			}

			// Skapar Karakt�rerna n�r red = 100
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

	image.loadFromFile("Maps/" + imageNameObject);

	for(int i = 0; i < image.getSize().x; ++i)
	{
		for(int j = 0; j < image.getSize().y; ++j)
		{
			sf::Color color = image.getPixel(i ,j);
			sf::Vector2f position = sf::Vector2f(i * 64.f, j *64.f);

			// Skapar Object vid Red = 200
			if(color.r == 200 && color.a == 255)
			{
				if(color.g == 0) // h�ger :-P Sista f�rgen avg�r skut intervallet i tiondels sekunder
				{
					entityManager->addEntity(new ShottingTrap(position, color.b, true, false));
				}
				else if(color.g == 50) // v�nster :-b
				{
					entityManager->addEntity(new ShottingTrap(position,color.b ,true, true));
				}
				else if(color.g == 100)
				{
					entityManager->addEntity(new SpikeBlock(position));
				}
				else if(color.g == 150)// liten som f�jrer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, false, true));
				}
				else if(color.g == 155)// stor som f�ljer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, true, true));
				}
				else if(color.g == 160)// liten som INTE f�jrer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, false, false));
				}
				else if(color.g == 170)// stor som INTE f�ljer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, true, false));
				}
				else if(color.g == 180)// st�rre som f�jrer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, false, true, true));
				}
				else if(color.g == 190)// st�rre som INTE f�ljer bakgrund
				{
					entityManager->addEntity(new Decoration(position, color.b, false, false, true));
				}
				else if(color.g == 250)
				{
					entityManager->addEntity(new TutorialSign(position, color.b));
				}
			}
		}
	}
}