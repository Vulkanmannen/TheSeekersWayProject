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
#include "MyLightSystem.h"

#include <LTBL\Light\LightSystem.h>
#include <LTBL\Light\Light_Point.h>
#include <LTBL\Utils.h>

int main()
{
	sf::VideoMode videoMode(1024, 720);
	sf::RenderWindow window(videoMode, "The Seekers Way"/*, sf::Style::Fullscreen*/);
	ImageManager::setWindow(&window);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::View view;
	view.setCenter(512, 360);
	view.setSize(1024, 720);

	ltbl::LightSystem lightSystem = ltbl::LightSystem(AABB(Vec2f(0.0f, 0.0f), Vec2f(view.getSize().x , view.getSize().y)), 
		&ImageManager::getWindow(), "lightFin.png", "shaders/lightAttenuationShader.frag");

	lightSystem.m_ambientColor = sf::Color(80,80,80);
	lightSystem.m_useBloom = true;
	

	// sätter ett lightsystem till lightmanagern
	MyLightSystem::setLightSystem(&lightSystem);

	window.setMouseCursorVisible(false);

	Sounds::getInstance();

	EntityManager::getInstance()->setView(&view, &videoMode);

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
		lightSystem.SetView(view);
		
		window.display();
    }
	delete EntityManager::getInstance();
	delete Dialogue::getInstance();
	delete Sounds::getInstance();
    return 0;
}
