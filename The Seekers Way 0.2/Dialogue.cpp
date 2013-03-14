#include "Dialogue.h"
#include <cassert>
#include "ImageManager.h"

#include <iostream>

Dialogue* Dialogue::sInstance = 0;
const static float HEIGHT = 128;
const static float WIDTH = 64;

Dialogue::Dialogue():
	mEndofDialogue(true),
	isbuttonpressed(false),
	currentText(0),
	dialogSpeed(10),
	currentLetter(0),
	mStartDialogue(true)
{
	/*journal_font = new sf::Font;
	if(!journal_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");

	character_font = new sf::Font(journal_font->getDefaultFont());*/
	/*if(!character_font->loadFromFile("journal.ttf"))
		assert(!"FONT NOT LOADED");
	character_font->loadFromFile("");*/
	mTexture[0].loadFromImage(*ImageManager::getImage("dialog0.png"));
	mTexture[1].loadFromImage(*ImageManager::getImage("dialog1.png"));
	mTexture[2].loadFromImage(*ImageManager::getImage("dialog2.png"));
	mTexture[3].loadFromImage(*ImageManager::getImage("dialog3.png"));

}

Dialogue::~Dialogue()
{
	empthyDialogue();
	/*
	delete journal_font;
	delete character_font;*/
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
		if(dialogs.size() != 0)
		{
			if(currentText < dialogs.size())
			{
				if(currentLetter < dialogs[currentText]->text.getString().toAnsiString().size() )
				{	
					currentLetter++;
				}
				if(dialogs[currentText]->speaker != 4)
				{
					EntityManager::getInstance()->setPrimaryCharacter(static_cast<Entity::EntityKind>(dialogs[currentText]->speaker));
					EntityManager::getInstance()->setShadeAll(false);
				}
				else if(dialogs[currentText]->speaker == 4)
				{
					EntityManager::getInstance()->setShadeAll(true);
				}
			}
		}
	}
	/*if(interval.getElapsedTime().asMilliseconds() > dialogSpeed)
	{
		interval.restart();
		if(texts.size() != 0)
		{
			if(currentText < texts.size())
			{
				if(currentLetter < texts[currentText]->getString().toAnsiString().size() )
				{	
					currentLetter++;
				}
				EntityManager::getInstance()->setPrimaryCharacter(static_cast<Entity::EntityKind>(speakerlista[texts[currentText]]));
			}
		}
	}*/
	playNext();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		
		EntityManager::getInstance()->setShadeAll(false);
		EntityManager::getInstance()->setEmotion(0, 0);
		EntityManager::getInstance()->setEmotion(1, 0);
		EntityManager::getInstance()->setEmotion(2, 0);
		EntityManager::getInstance()->setEmotion(3, 0);
		mEndofDialogue = true;
	}
}

void Dialogue::render()
{
	if(!mEndofDialogue)
	{
		if(currentText < dialogs.size())
		{
			
			float	camX = EntityManager::getInstance()->getView()->getCenter().x - EntityManager::getInstance()->getView()->getSize().x/2, 
					camY = EntityManager::getInstance()->getView()->getCenter().y - EntityManager::getInstance()->getView()->getSize().y/2;
			sf::Text tempText;
			tempText.setFont(getfont(dialogs[currentText]->fontnamn));
			std::string tempString;
			if(dialogs[currentText]->text.getString().toAnsiString().size() != 0)
			{
				tempString = dialogs[currentText]->text.getString().toAnsiString().substr(0, currentLetter);
			}
			else
			{
				tempString = dialogs[currentText]->text.getString().toAnsiString();
			}
			tempText.setString(tempString);
			mSprite.setPosition(	sf::Vector2f(camX + dialogs[currentText]->bildposition.x, camY + dialogs[currentText]->bildposition.y));
			tempText.setPosition(	sf::Vector2f(camX + dialogs[currentText]->textposition.x, camY + dialogs[currentText]->textposition.y));
			sf::Texture temptexture;
			if(dialogs[currentText]->bildnamn == "")
			{
				mSprite.setTexture(mTexture[dialogs[currentText]->speaker]);
			}
			else
			{
				temptexture.loadFromImage(*ImageManager::getImage(dialogs[currentText]->bildnamn));
				mSprite.setTexture(temptexture);
			}
			tempText.setCharacterSize(dialogs[currentText]->size);
			tempText.setColor(dialogs[currentText]->color);
			EntityManager::getInstance()->setEmotion(int(dialogs[currentText]->speaker), int(dialogs[currentText]->emotion));
			ImageManager::render(&mSprite);
			ImageManager::render(&tempText);
		}
		/*if(currentText < texts.size())
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

		}*/
		else
		{
			EntityManager::getInstance()->setShadeAll(false);
			EntityManager::getInstance()->setEmotion(0, 0);
			EntityManager::getInstance()->setEmotion(1, 0);
			EntityManager::getInstance()->setEmotion(2, 0);
			EntityManager::getInstance()->setEmotion(3, 0);
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
	//loadDialogue(dialogueName);
	load(dialogueName);
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
	while(!dialogs.empty())
	{
		//delete dialogs.back()->text;
		delete dialogs.back();
		dialogs.pop_back();
	}
}

void Dialogue::load(std::string dialogueName)
{
	sDocument.LoadFile(("Dialoger/" + dialogueName + ".xml").c_str());
	TiXmlElement* root = sDocument.FirstChildElement("Body");
	root = root->FirstChildElement("Dialog");
	while(root)
	{

		TiXmlAttribute* attribute = root->FirstAttribute();
		std::string string = attribute->Name();

		if(std::strcmp(string.c_str(), "name") == 0)
		{
			dialogbase tempDialog;

			//
			//-------------------------------------------------------------------- door
			//
			TiXmlElement* element;

			element = root->FirstChildElement("speech");
			if(element)
			{

				TiXmlAttribute* positionAttribute = element->FirstAttribute();
				while(positionAttribute)
				{
					std::string name = positionAttribute->Name();
					if(name == "bild")
					{
						tempDialog.bildnamn = positionAttribute->Value();
					}
					else if(name == "bildX")
					{
						tempDialog.bildposition.x = static_cast<float>(positionAttribute->IntValue());
					}
					else if(name == "bildY")
					{
						tempDialog.bildposition.y = static_cast<float>(positionAttribute->IntValue());
					}
					else if(name == "text")
					{
						tempDialog.text.setString(positionAttribute->Value());
					}
					else if(name == "textX")
					{
						tempDialog.textposition.x = static_cast<float>(positionAttribute->IntValue());
					}
					else if(name == "textY")
					{
						tempDialog.textposition.y = static_cast<float>(positionAttribute->IntValue());
					}
					else if(name == "speaker")
					{
						tempDialog.speaker = Speaker(positionAttribute->IntValue());
					}
					else if(name == "size")
					{
						tempDialog.size = (positionAttribute->IntValue());
					}
					else if(name == "font")
					{
						tempDialog.fontnamn = positionAttribute->Value();
					}
					else if(name == "textboxWidth")
					{
						tempDialog.textbox.x = positionAttribute->IntValue();
					}
					else if(name == "textboxHeight")
					{
						tempDialog.textbox.y = positionAttribute->IntValue();
					}
					else if(name == "emotion")
					{
						tempDialog.emotion = Emotion(positionAttribute->IntValue());
					}
					else if(name == "color")
					{
						if(positionAttribute->Value() == "black")
						{
							tempDialog.color = tempDialog.color.Black;
						}
						if(positionAttribute->Value() == "white")
						{
							tempDialog.color = tempDialog.color.White;
						}
					}
					else if(name == "colorR")
					{
						tempDialog.color.r = positionAttribute->IntValue();
					}
					else if(name == "colorG")
					{
						tempDialog.color.g = positionAttribute->IntValue();
					}
					else if(name == "colorB")
					{
						tempDialog.color.b = positionAttribute->IntValue();
					}
					else if(name == "colorA")
					{
						tempDialog.color.a = positionAttribute->IntValue();
					}
					positionAttribute = positionAttribute->Next();
				}
			}

			TextVector temptext = textBox(tempDialog.text, tempDialog.textbox, tempDialog.size, tempDialog.fontnamn);
			
			for(int i = 0; temptext.size() > i; i++)
			{
				dialogbase *okDialog = new dialogbase(tempDialog);
				okDialog->text.setString(temptext[i]->getString().toAnsiString());
				dialogs.push_back(okDialog);
			}
			while(!temptext.empty())
			{
				delete temptext.back();
				temptext.pop_back();
			}
		}
		root = root->NextSiblingElement("Dialog");
	}
}

void Dialogue::loadDialogue(std::string dialogueName)
{
//	std::ifstream fil("Dialogues/" + dialogueName);
//	std::string file;
//	char backslash = 92;
//	Speaker speaker = kiba;
//	while(!fil.eof())
//	{
//		std::getline(fil, file, backslash);
//		std::string filen;
//		filen =	file.substr(	0, file.find('/'));
//		if(file.find('/') != std::string::npos)
//		{
//			file.erase(		0, file.find('/') + 1);
//		}
//		else 
//		{
//			file.erase(		0, file.find('/'));
//		}
//		if(	filen.find('1') != std::string::npos || 
//			filen.find('2') != std::string::npos || 
//			filen.find('3') != std::string::npos || 
//			filen.find('4') != std::string::npos)
//		{
//			int i = 0;
//			std::vector<int> j;
//			filen.find('1') != std::string::npos ? j.push_back(filen.find('1')) : NULL;
//			filen.find('2') != std::string::npos ? j.push_back(filen.find('2')) : NULL;
//			filen.find('3') != std::string::npos ? j.push_back(filen.find('3')) : NULL;
//			filen.find('4') != std::string::npos ? j.push_back(filen.find('4')) : NULL;
//			for(int o = 0; o < j.size(); o++)
//			{
//				if(j[o] < j[i])
//				{
//					i = o;
//				}
//			}
//			switch(filen[j[i]])
//			{
//				case '1':
//					speaker = kiba;
//					break;
//				case '2':
//					speaker = charlotte;
//					break;
//				case '3':
//					speaker = fenrir;
//					break;
//				case '4':
//					speaker = sheeka;
//					break;
//			}
//
//		}
//
//		while(!file.empty())
//		{
//			std::string filnamn, oldest, newest;
//			filnamn =	file.substr(	0, file.find('\n'));
//			file.erase(					0, file.find('\n'));
//			file.erase(0,1);
//			while(!filnamn.empty())
//			{
//				while(filnamn.rfind(' ') == 0 || filnamn.rfind('\n') == 0)
//				{
//					filnamn.erase(0, 1);
//				}
//				newest = filnamn[0];
//				oldest = "";
//				sf::Text *text = new sf::Text;
//				text->setFont(*character_font);
//				for(bool j = true; j == true;)
//				{
//					//std::cout<<oldest<<std::endl;
//					//std::cout<<newest<<std::endl;
//					//std::cout<<filnamn<<std::endl;
//
//					text->setString(sf::String(newest.c_str()));
//					if(filnamn.length() > 1)
//					{
//						if(text->getLocalBounds().width < 300 && text->getLocalBounds().height < 110)
//						{
//							oldest = newest;
//							newest += filnamn[1];
//							filnamn = filnamn.substr(1);
//						}
//						else 
//						{
//							if(text->getLocalBounds().height < 110)
//							{
//								bool split = true;
//								if(newest.rfind(' ') != std::string::npos && newest.rfind('\n') != std::string::npos)
//								{
//									if(newest.rfind(' ') > newest.rfind('\n'))
//									{
//										split = false;
//									}
//								}
//								else if(newest.rfind(' ') != std::string::npos && newest.rfind('\n') == std::string::npos)
//								{
//									split = false;
//								}
//
//								switch(split)
//								{
//								case true:
//									newest = oldest + '\n' + newest.back();
//									break;
//								case false:
//									newest.insert(newest.rfind(' ') + 1, "\n");
//									oldest = newest.substr(0, newest.size() - 1);
//									break;
//								}
//							}
//							else
//							{
//								filnamn = oldest.substr(oldest.rfind(' ') + 1) + filnamn;
//								oldest = oldest.substr(0, oldest.rfind(' '));
//
//								text->setString(sf::String(oldest.c_str()));
//								j = false;
//							}
//						}
//					}
//					else
//					{
//						filnamn.erase(0, 1);
//						j = false;
//					}
//				}
//				speakerlista.insert(std::pair<sf::Text*, Speaker>(text, speaker));
//				texts.push_back(text);
//			}
//			filnamn.clear();
//		}
//	}
}

void Dialogue::playNext()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(!isbuttonpressed)
		{
			if(currentLetter >= dialogs[currentText]->text.getString().toAnsiString().size())
			{
				currentText++;
				currentLetter = 0;
			}
			else
			{
				currentLetter = dialogs[currentText]->text.getString().toAnsiString().size() - 1;
			}
			isbuttonpressed = true;
		}
	}
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
	}*/
	else
	{
		isbuttonpressed = false;
	}
}


Dialogue::TextVector Dialogue::textBox(sf::Text &rawText, sf::Vector2f textboxsize, int textsize, std::string fontnamn)
{
	TextVector om;
	
	std::string file = rawText.getString().toAnsiString();

	while(!file.empty())
	{
		std::string filnamn, oldest, newest;
		filnamn =	file.substr(	0, file.find('\n'));
		file.erase(					0, file.find('\n'));
		file.erase(0,1);
		while(!filnamn.empty())
		{
			while(filnamn.rfind(' ') == 0 || filnamn.rfind('\n') == 0)
			{
				filnamn.erase(0, 1);
			}
			newest = filnamn[0];
			oldest = "";
			sf::Text *text = new sf::Text;
			text->setFont(getfont(fontnamn));
			text->setCharacterSize(textsize);
			for(bool j = true; j == true;)
			{
				//std::cout<<oldest<<std::endl;
				//std::cout<<newest<<std::endl;
				//std::cout<<filnamn<<std::endl;

				text->setString(sf::String(newest.c_str()));
				if(filnamn.length() > 1)
				{
					if(text->getLocalBounds().width < textboxsize.x && text->getLocalBounds().height < textboxsize.y)
					{
						oldest = newest;
						newest += filnamn[1];
						filnamn = filnamn.substr(1);
					}
					else 
					{
						if(text->getLocalBounds().height < textboxsize.y)
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
			om.push_back(text);
		}
		filnamn.clear();
	}
	return om;
}

bool Dialogue::getStartDialogue()const
{
	return mStartDialogue;
}

void Dialogue::setStartDialogue(bool startDialogue)
{
	mStartDialogue = startDialogue;
}

sf::Font& Dialogue::getfont(std::string string)
{
	if(fonts[string] == NULL)
	{
		fonts[string] = new sf::Font;
		fonts[string]->loadFromFile("Fonts/" + string);
		if(!fonts[string]->loadFromFile("Fonts/" + string))
		{
			assert(!"FONT NOT LOADED");
		}
	}
	return *fonts[string];
}
