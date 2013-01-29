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

void GenerateDoor::GenerateDoors()
{

	TiXmlElement* root = sDocument.FirstChildElement("Body");
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
					positionAttribute = positionAttribute->Next();
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
					positionAttribute = positionAttribute->Next();
				}
			}
			EntityManager* manager = EntityManager::getInstance();
			Door* door = new Door(sf::Vector2f(doorPosX, doorPosY));
			manager->addEntity(door);
			manager->addEntity(new Button(sf::Vector2f(leverPosX, leverPosY), door));
		}
		root = root->NextSiblingElement("Door");
	}
}

void GenerateDoor::loadDocument(std::string s)
{
	sDocument.LoadFile(s.c_str());
}