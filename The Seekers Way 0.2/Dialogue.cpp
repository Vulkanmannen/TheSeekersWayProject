#include "Dialogue.h"
#include <cassert>
#include "ImageManager.h"
#include "EntityManager.h"
#include <iostream>

Dialogue* Dialogue::sInstance = 0;
const static float HEIGHT = 128;
const static float WIDTH = 64;

Dialogue::Dialogue():
	mEndofDialogue(true),
	isbuttonpressed(false),
	currentText(0)
{
	
	journal_font = new sf::Font;
	if(!journal_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");

	character_font = new sf::Font;
	if(!character_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");

	mTexture.loadFromImage(*ImageManager::getImage("dialog0.png"));
	mSprite.setTexture(mTexture);
}

Dialogue::~Dialogue()
{
	empthyDialogue();
	delete journal_font;
	delete character_font;
}

Dialogue* Dialogue::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new Dialogue;
	}
	return sInstance;
}

void Dialogue::update()
{
	playNext();
}

void Dialogue::render()
{
	if(!mEndofDialogue)
	{
		if(currentText < texts.size())
		{
			mSprite.setPosition(			EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512		, 360 - 84));
			texts[currentText]->setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512 - 10, 360 - 94));
			ImageManager::render(&mSprite);
			ImageManager::render(texts[currentText]);
		}
		else
		{
			mEndofDialogue = true;
		}
	}
}

bool Dialogue::getendofDialogue()
{
	return mEndofDialogue;
}


void Dialogue::startDialogue(std::string dialogueName)
{
	currentText = 0;
	empthyDialogue();
	loadDialogue(dialogueName);
	mEndofDialogue = false;
}

void Dialogue::empthyDialogue()
{
	while(!texts.empty())
		{
			delete texts.back();
			texts.pop_back();
		}
}

void Dialogue::loadDialogue(std::string dialogueName)
{
	std::ifstream fil(dialogueName);
	while(!fil.eof())
	{
		std::string filnamn, oldest, newest;
		std::getline(fil, filnamn, '\n');
		while(!filnamn.empty())
		{
			while(filnamn.rfind(' ') == 0 || filnamn.rfind('\n') == 0)
			{
				filnamn.erase(0, 1);
			}
			newest = filnamn[0];
			oldest = "";
			sf::Text *text = new sf::Text;
			text->setFont(*journal_font);
			for(bool j = true; j == true;)
			{
				//std::cout<<oldest<<std::endl;
				//std::cout<<newest<<std::endl;
				//std::cout<<filnamn<<std::endl;

				text->setString(sf::String(newest.c_str()));
				if(filnamn.length() > 1)
				{
					if(text->getLocalBounds().width < 300 && text->getLocalBounds().height < 110)
					{
						oldest = newest;
						newest += filnamn[1];
						filnamn = filnamn.substr(1);
					}
					else 
					{
						if(text->getLocalBounds().height < 110)
						{
							bool split = true;
							if(newest.rfind(' ') != std::string::npos && newest.rfind('\n') != std::string::npos)
							{
								if(newest.rfind(' ') > newest.rfind('\n'))
								{
									split = false;
								}
							}
							else if(newest.rfind(' ') != std::string::npos && newest.rfind('\n') == std::string::npos)
							{
								split = false;
							}

							switch(split)
							{
							case true:
								newest = oldest + '\n' + newest.back();
								break;
							case false:
								newest.insert(newest.rfind(' ') + 1, "\n");
								oldest = newest.substr(0, newest.size() - 1);
								break;
							}
						}
						else
						{
							filnamn = oldest.substr(oldest.rfind(' ') + 1) + filnamn;
							oldest = oldest.substr(0, oldest.rfind(' '));

							text->setString(sf::String(oldest.c_str()));
							j = false;
						}
					}
				}
				else
				{
					filnamn.erase(0, 1);
					j = false;
				}
			}
			texts.push_back(text);
		}
		filnamn.clear();
	}
}

void Dialogue::playNext()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if(!isbuttonpressed)
		{
			currentText++;
			isbuttonpressed = true;
		}
	}
	else
	{
		isbuttonpressed = false;
	}
}


Dialogue::TextVector Dialogue::textBox(sf::Text &rawText)
{
TextVector om;
	return om;
}