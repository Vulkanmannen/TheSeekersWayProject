#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "EntityManager.h"
#include "MapGenerator.h"
#include "NormalBlock.h"
#include "Animation.h"

#include <string>

#include "Door.h"
#include "Button.h"
#include "Lever.h"
#include "ShottingTrap.h"
#include "Sounds.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 720), "The Seekers Way"/*, sf::Style::Fullscreen*/);
	ImageManager::setWindow(&window);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
<<<<<<< HEAD
	std::string map1("Map2.png");
	MapGenerator::generateMap(map1);
	//EntityManager::getInstance()->addEntity(new Door(sf::Vector2f(5 *64,4 *64)));
	//EntityManager::getInstance()->addEntity(new Door(sf::Vector2f(4 *64 ,4 *64)));
	//EntityManager::getInstance()->addEntity(new Button(sf::Vector2f(0,0)));
	//EntityManager::getInstance()->addEntity(new Lever(sf::Vector2f(0,0)));
=======
	sf::View view;
	view.setSize(1024, 720);

	std::string map1("map1.png");
	MapGenerator::generateMap(map1);

	//Block *Door1 = new Door(sf::Vector2f(5 *64,4 *64));
	//Block *Door2 = new Door(sf::Vector2f(4 *64,4 *64));
	//EntityManager::getInstance()->addEntity(Door1);
	//EntityManager::getInstance()->addEntity(Door2);
	//EntityManager::getInstance()->addEntity(new Button(sf::Vector2f(2*64,3 *64), Door1));
	//EntityManager::getInstance()->addEntity(new Lever(sf::Vector2f(3*64,3 *64), Door2));
	//kolla entitymanagaer i colision
	Sounds::getInstance()->Loop("Levelkoncept 2.wav");
>>>>>>> 19b9601d2dbc174ffc90bc278e2702e5bbc3f5cb

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear(sf::Color::Blue);

		EntityManager::getInstance()->update();
		EntityManager::getInstance()->render();

		view.setCenter(EntityManager::getInstance()->getCharacterPos());
		window.setView(view);

		EntityManager::getInstance()->primaryCharacter();

		window.display();
    }

    return 0;
}
