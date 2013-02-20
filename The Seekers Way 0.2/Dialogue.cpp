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
	currentText(0),
	dialogSpeed(10),
	currentLetter(0)
{
	
	journal_font = new sf::Font;
	if(!journal_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");

	character_font = new sf::Font(journal_font->getDefaultFont());
	/*if(!character_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");*/

	mTexture[0].loadFromImage(*ImageManager::getImage("dialog0.png"));
	mTexture[1].loadFromImage(*ImageManager::getImage("dialog1.png"));
	mTexture[2].loadFromImage(*ImageManager::getImage("dialog2.png"));
	mTexture[3].loadFromImage(*ImageManager::getImage("dialog3.png"));

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
	if(interval.getElapsedTime().asMilliseconds() > dialogSpeed)
	{
		interval.restart();
		if(currentLetter < texts[currentText]->getString().toAnsiString().size() )
		{
			currentLetter++;
		}
	}
	playNext();
}

void Dialogue::render()
{
	if(!mEndofDialogue)
	{
		if(currentText < texts.size())
		{
			sf::Text tempText;
			tempText.setFont(*character_font);
			std::string tempString;
			if(texts[currentText]->getString().toAnsiString().size() != 0)
			{
				tempString = texts[currentText]->getString().toAnsiString().substr(0, currentLetter);
			}
			else
			{
				tempString = texts[currentText]->getString().toAnsiString();
			}
			tempText.setString(tempString);
			mSprite.setPosition(			EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512		, 360 - 84));
			tempText.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512 - 10, 360 - 94));
			mSprite.setTexture(mTexture[speakerlista[texts[currentText]]]);
			ImageManager::render(&mSprite);
			ImageManager::render(&tempText);
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
	currentLetter = 0;
	empthyDialogue();
	loadDialogue(dialogueName);
	mEndofDialogue = false;
	interval.restart();
}

void Dialogue::empthyDialogue()
{
	while(!texts.empty())
		{
			delete texts.back();
			texts.pop_back();
		}
	speakerlista.clear();
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
			text->setFont(*character_font);
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
			speakerlista.insert(std::pair<sf::Text*, Speaker>(text, kiba));
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
			if(currentLetter >= texts[currentText]->getString().toAnsiString().size())
			{
				currentText++;
				currentLetter = 0;
			}
			else
			{
				currentLetter = texts[currentText]->getString().toAnsiString().size() - 1;
			}
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