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
#include "BigBridge.h"
#include "Stone.h"

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

	Stone* stone = new Stone(sf::Vector2f(17 *64, 0 *64));
	EntityManager::getInstance()->addEntity(new Stone(sf::Vector2f(17 *64, 0 *64)));
	EntityManager::getInstance()->addEntity(stone);
	sf::Clock clock;
	//Sounds::getInstance()->Loop("Levelkoncept.wav", 30);
    while (window.isOpen())
    {
        sf::Event event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{	
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && clock.getElapsedTime().asSeconds() > 1)
		{	
			stone->mtelekinesis = !stone->mtelekinesis;
			clock.restart();
		}

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
	delete EntityManager::getInstance();
    return 0;
}
