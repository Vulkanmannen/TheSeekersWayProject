#include "GenerateDoor.h"
#include <string>
#include "EntityManager.h"
#include "Door.h"
#include "Lever.h"
#include "Button.h"
#include "SFML\Graphics.hpp"

TiXmlDocument GenerateDoor::sDocument;

GenerateDoor::GenerateDoor()
	{}


GenerateDoor::~GenerateDoor()
	{}

void GenerateDoors(TiXmlDocument &document)
{
	TiXmlElement* root = document.FirstChildElement("Body");
	root = root->FirstChildElement("Door");
	
	while(root)
	{
		TiXmlAttribute* attribute = root->FirstAttribute();
		std::string string = attribute->Name();
		if(string == "name")
		{
			float doorPosX, doorPosY, leverPosX, leverPosY;
			TiXmlElement* element = root->FirstChildElement("doorPosition");
			if(element)
			{
				TiXmlAttribute* positionAttribute = element->FirstAttribute();
				while(positionAttribute)
				{
					std::string name = positionAttribute->Name();
					if(name == "X")
					{
						doorPosX = static_cast<float>(positionAttribute->IntValue());
					}
					if(name == "Y")
					{
						doorPosY = static_cast<float>(positionAttribute->IntValue());
					}
				}
			}
			element = root->FirstChildElement("leverPosition");
			if(element)
			{
				TiXmlAttribute* positionAttribute = element->FirstAttribute();
				while(positionAttribute)
				{
					std::string name = positionAttribute->Name();
					if(name == "X")
					{
						leverPosX = static_cast<float>(positionAttribute->IntValue());
					}
					if(name == "Y")
					{
						leverPosY = static_cast<float>(positionAttribute->IntValue());
					}
				}
			}
			EntityManager* manager = EntityManager::getInstance();
			//manager->addEntity(new Door(sf::Vector2f(doorPosX, doorPosY)));
			//manager->addEntity(new Lever(sf::Vector2f(leverPosX, leverPosY)));
		}
	}
}

void GenerateDoor::loadDocument(std::string &s)
{

}