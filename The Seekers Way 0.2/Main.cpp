#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "EntityManager.h"
#include "MapGenerator.h"
#include "NormalBlock.h"
#include "Animation.h"
#include "StartMenu.h"

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
	ImageManager::setWindow(&window);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::View view;
	view.setSize(1024, 720);

	window.setMouseCursorVisible(false);

	EntityManager::getInstance()->setView(&view);

	Sounds::getInstance();


	/*Sounds::getInstance()->Loop("Level1Music.wav", 30);*/

    while (window.isOpen())
    {
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
		view.setCenter(sf::Vector2f(512, 360));
		State::getInstance()->update();
		
		//if(Dialogue::getInstance()->getendofDialogue())
		//{
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		//	{	
		//		Dialogue::getInstance()->startDialogue("start1.txt");
		//	}
		//}
		//else
		//{
		//	Dialogue::getInstance()->update();
		//	Dialogue::getInstance()->render();
		//}

		window.setView(view); 

		window.display();
    }
	delete EntityManager::getInstance();
	delete Dialogue::getInstance();
	delete Sounds::getInstance();
    return 0;
}
