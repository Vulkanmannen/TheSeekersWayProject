#include "GenerateDoor.h"
#include <string>
#include "EntityManager.h"
#include "Door.h"
#include "Lever.h"
#include "Button.h"
#include "SFML\Graphics.hpp"
#include "MagicSwitch.h"
#include "BigBridge.h"
#include "Bridge.h"
#include "Portal.h"

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
	enum BrigeOrDoor {DOOR, BIGBRIDGE, SMALBRIDGE};
	
	while(root)
	{

		TiXmlAttribute* attribute = root->FirstAttribute();
		std::string string = attribute->Name();
		
		DoorWith doorWith;
		BrigeOrDoor brigeOrDoor;

		if(string == "name")
		{
			float doorPosX, doorPosY, leverPosX, leverPosY, timeOpen;
			std::string texture;
			bool closed = true;
			
			//
			//-------------------------------------------------------------------- door
			//
			TiXmlElement* element;

			element = root->FirstChildElement("doorPosition");
			if(element)
			{
				brigeOrDoor = DOOR;

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
					if(name == "texture")
					{
						texture = positionAttribute->Value();
					}
					positionAttribute = positionAttribute->Next();
				}
			}

			//
			//---------------------------------------------------------bigbrige
			//
			element = root->FirstChildElement("bigBridgePosition");
			if(element)
			{
				brigeOrDoor = BIGBRIDGE;

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
					if(name == "Closed")
					{
						closed = positionAttribute->IntValue();
					}
					positionAttribute = positionAttribute->Next();
				}
			}

			//
			//---------------------------------------------------------smalbrige
			//
			element = root->FirstChildElement("smalBridgePosition");
			if(element)
			{
				brigeOrDoor = SMALBRIDGE;

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
					if(name == "Closed")
					{
						closed = positionAttribute->IntValue();
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
			Entity* block;
			if(brigeOrDoor == DOOR)
			{
				if(texture.empty())
				{
					block = new Door(sf::Vector2f(doorPosX, doorPosY));
				}
				else
				{
					block = new Door(sf::Vector2f(doorPosX, doorPosY), texture);
				}
			}
			else if(brigeOrDoor == BIGBRIDGE)
			{
				block = new BigBridge(sf::Vector2f(doorPosX, doorPosY), closed);
			}
			else if(brigeOrDoor == SMALBRIDGE)
			{
				block = new Bridge(sf::Vector2f(doorPosX, doorPosY), closed);
			}
			
			manager->addEntity(block);

			// skapar spak
			if(doorWith == LEVER)
			{
				manager->addEntity(new Lever(sf::Vector2f(leverPosX, leverPosY), static_cast<Block*>(block)));
			}
			else if(doorWith == BUTTON)
			{
				manager->addEntity(new Button(sf::Vector2f(leverPosX, leverPosY), static_cast<Block*>(block)));
			}		
			else if(doorWith == MAGICSWITCH)
			{
				manager->addEntity(new MagicSwitch(sf::Vector2f(leverPosX, leverPosY), static_cast<Block*>(block), timeOpen));
			}
		}
		root = root->NextSiblingElement("Door");
	}

	//
	//----------------------------------------------------------------------------------------portal
	//
	root = sDocument.FirstChildElement("Body2");
	root = root->FirstChildElement("Portal");

	while(root)
	{
		TiXmlAttribute* attribute = root->FirstAttribute();
		std::string string = attribute->Name();

		if(string == "name")
		{
			float X1, Y1, X2, Y2;
			TiXmlElement* element;

			element = root->FirstChildElement("portalPosition");

			if(element)
			{
				TiXmlAttribute* positionAttribute = element->FirstAttribute();
				while(positionAttribute)
				{
					std::string name = positionAttribute->Name();
					if(name == "X1")
					{
						X1 = static_cast<float>(positionAttribute->IntValue());
					}
					if(name == "Y1")
					{
						Y1 = static_cast<float>(positionAttribute->IntValue());
					}
					if(name == "X2")
					{
						X2 = static_cast<float>(positionAttribute->IntValue());
					}
					if(name == "Y2")
					{
						Y2 = static_cast<float>(positionAttribute->IntValue());
					}
					positionAttribute = positionAttribute->Next();
				}
			}	
			EntityManager::getInstance()->addEntity(new Portal(sf::Vector2f(X1, Y1), sf::Vector2f(X2, Y2)));
		}
		root = root->NextSiblingElement("Portal");
	}

}

void GenerateDoor::loadDocument(std::string s)
{
	sDocument.LoadFile(s.c_str());
}