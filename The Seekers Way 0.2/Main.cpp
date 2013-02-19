#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "EntityManager.h"
#include "MapGenerator.h"
#include "NormalBlock.h"
#include "Animation.h"

#include <string>

#include "State.h"
#include "Door.h"
#include "Button.h"
#include "Lever.h"
#include "ShottingTrap.h"
#include "Sounds.h"
#include "BigBridge.h"
#include "Stone.h"
#include "WoodenWall.h"
#include "Portal.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 720), "The Seekers Way"/*, sf::Style::Fullscreen*/);
	ImageManager::setWindow(&window);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::View view;
	view.setSize(1024, 720);

	EntityManager::getInstance()->setView(&view);

	std::string map1("Totteebest.PNG");
	MapGenerator::generateMap(map1);

	//EntityManager::getInstance()->addEntity(new WoodenWall(sf::Vector2f(17 *64, 13 *64)));

	sf::Clock clock;
	//Sounds::getInstance()->Loop("Levelkoncept.wav", 30);

	State state;
    while (window.isOpen())
    {
        sf::Event event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{	
			window.close();
		}

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		window.clear(sf::Color::Blue);
		view.setCenter(sf::Vector2f(512, 360));
		state.update();

		window.setView(view);

		window.display();
    }
	delete EntityManager::getInstance();
    return 0;
}
