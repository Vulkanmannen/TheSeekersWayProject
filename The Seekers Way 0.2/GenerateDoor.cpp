#include "GenerateDoor.h"
#include <string>
#include "EntityManager.h"
#include "Door.h"
#include "Lever.h"
#include "Button.h"
#include "SFML\Graphics.hpp"
#include "MagicSwitch.h"

TiXmlDocument GenerateDoor::sDocument;

GenerateDoor::GenerateDoor()
	{}


GenerateDoor::~GenerateDoor()
	{}

void GenerateDoor::GenerateDoors()
{

	TiXmlElement* root = sDocument.FirstChildElement("Body");
	root = root->FirstChildElement("Door");
	enum DoorWith {LEVER, BUTTON, MAGICSWITCH};
	
	while(root)
	{
		//
		//-------------------------------------------------------------------- door
		//
		TiXmlAttribute* attribute = root->FirstAttribute();
		std::string string = attribute->Name();
		
		DoorWith doorWith;

		if(string == "name")
		{
			float doorPosX, doorPosY, leverPosX, leverPosY, timeOpen;
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
			//
			//-------------------------------------------------------------------- lever
			//
			element = root->FirstChildElement("leverPosition");
			if(element)
			{
				doorWith = LEVER;

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
			//
			//-------------------------------------------------------------------- button
			//
			element = root->FirstChildElement("buttonPosition");
			if(element)
			{
				doorWith = BUTTON;

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
			//
			//--------------------------------------------------------------------magic switch
			//
			element = root->FirstChildElement("magicSwitchPosition");
			if(element)
			{
				doorWith = MAGICSWITCH;

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
					if(name == "timeOpen")
					{
						timeOpen = static_cast<float>(positionAttribute->IntValue());
					}

					positionAttribute = positionAttribute->Next();
				}
			}

			// skapar dörren
			EntityManager* manager = EntityManager::getInstance();
			Door* door = new Door(sf::Vector2f(doorPosX, doorPosY));
			manager->addEntity(door);
			if(doorWith == LEVER)
			{
				manager->addEntity(new Lever(sf::Vector2f(leverPosX, leverPosY), door));
			}
			else if(doorWith == BUTTON)
			{
				manager->addEntity(new Button(sf::Vector2f(leverPosX, leverPosY), door));
			}		
			else if(doorWith == MAGICSWITCH)
			{
				manager->addEntity(new MagicSwitch(sf::Vector2f(leverPosX, leverPosY), door, timeOpen));
			}
		}
		root = root->NextSiblingElement("Door");
	}
}

void GenerateDoor::loadDocument(std::string s)
{
	sDocument.LoadFile(s.c_str());
}