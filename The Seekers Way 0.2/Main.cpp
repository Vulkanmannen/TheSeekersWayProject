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
	
	Block *Trap = new ShottingTrap(sf::Vector2f(19 *64,14 *64));
	EntityManager::getInstance()->addEntity(Trap);
	EntityManager::getInstance()->addEntity(new Button(sf::Vector2f(21 *64,13 *64), Trap));
	//kolla entitymanagaer i colision
	Sounds::getInstance()->Loop("Levelkoncept.wav", 30);

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

		EntityManager::getInstance()->updatePrimaryCharacter();

		window.display();
    }

    return 0;
}
