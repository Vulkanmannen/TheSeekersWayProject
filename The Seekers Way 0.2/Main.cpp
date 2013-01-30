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
	
	sf::View view;
	view.setSize(1024, 720);

	std::string map1("Tottemaptest.PNG");
	MapGenerator::generateMap(map1);
	
	Block *Dor = new Door(sf::Vector2f(5 *64,4 *64));
	Block *Trap = new ShottingTrap(sf::Vector2f(10 *64,2 *64),true);
	EntityManager::getInstance()->addEntity(Dor);
	EntityManager::getInstance()->addEntity(Trap);
	EntityManager::getInstance()->addEntity(new Button(sf::Vector2f(2*64,3 *64), Dor));
	EntityManager::getInstance()->addEntity(new Lever(sf::Vector2f(3*64,3 *64), Trap));
	//kolla entitymanagaer i colision
	Sounds::getInstance()->Loop("Levelkoncept 2.wav");

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
