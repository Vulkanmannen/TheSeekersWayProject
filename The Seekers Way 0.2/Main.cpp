#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "EntityManager.h"
#include "MapGenerator.h"
#include "NormalBlock.h"
#include "Animation.h"
#include "StartMenu.h"
#include "IntroScreen.h"

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
#include "Dialogue.h"


int main()
{	
	sf::RenderWindow window(sf::VideoMode(1024, 720), "The Seekers Way"/*, sf::Style::Fullscreen*/);
	//mVideo.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));

	ImageManager::setWindow(&window);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::View view;
	view.setCenter(512, 360);
	view.setSize(1024, 720);

	window.setMouseCursorVisible(false);

	EntityManager::getInstance()->setView(&view);

	Sounds::getInstance();

   while (window.isOpen())
    {
		sf::Listener::setPosition(view.getCenter().x, view.getCenter().y, 0);
        sf::Event event;

		if (State::getInstance()->getExit())
		{	
			window.close();
		}

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.clear(sf::Color::Black);
		State::getInstance()->update();

		window.setView(view); 

		window.display();
	}
	delete EntityManager::getInstance();
	delete Dialogue::getInstance();
	delete Sounds::getInstance();
    return 0;
}
