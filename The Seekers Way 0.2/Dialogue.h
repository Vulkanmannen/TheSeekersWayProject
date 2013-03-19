#ifndef INCLUDED_Dialogue
#define INCLUDED_Dialogue

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "tinyxml.h"
#include <map>
#include "EntityManager.h"

class Dialogue
{
	//typdefinitioner som bara klassen använder

	enum Speaker{kiba, charlotte, fenrir, sheeka, journal};
	enum Emotion{normal, sigh, happy, angry, surprised};
	
	struct dialogbase
	{
		sf::Vector2f	textposition;
		sf::Vector2f	bildposition;
		sf::Vector2f	textbox;
		sf::Text		text;
		std::string		bildnamn;
		std::string		fontnamn;
		float			size;
		Emotion			emotion;
		Speaker			speaker;
		sf::Color		color;

		dialogbase()
		{
			bildnamn		= "";
			bildposition	= sf::Vector2f(0, 84);
			emotion			= normal;
			fontnamn		= "segoeui.ttf";
			size			= 30U;
			speaker			= kiba;
			text.setString("");
			textbox			= sf::Vector2f(300, 110);
			textposition	= sf::Vector2f(10, 94);
			color			= sf::Color(255, 255, 255, 255);
			//defaultvärden som bestäms av en config fil
			{
				TiXmlDocument zDocument;
				zDocument.LoadFile("Dialoger/config.xml");
				TiXmlElement* root = zDocument.FirstChildElement("Body");
				root = root->FirstChildElement("Dialog");
				while(root)
				{
					TiXmlAttribute* attribute = root->FirstAttribute();
					std::string string = attribute->Name();
					if(std::strcmp(string.c_str(), "name") == 0)
					{
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
									bildnamn = positionAttribute->Value();
								}
								else if(name == "bildX")
								{
									bildposition.x = static_cast<float>(positionAttribute->IntValue());
								}
								else if(name == "bildY")
								{
									bildposition.y = static_cast<float>(positionAttribute->IntValue());
								}
								else if(name == "text")
								{
									text.setString(positionAttribute->Value());
								}
								else if(name == "textX")
								{
									textposition.x = static_cast<float>(positionAttribute->IntValue());
								}
								else if(name == "textY")
								{
									textposition.y = static_cast<float>(positionAttribute->IntValue());
								}
								else if(name == "speaker")
								{
									speaker = Speaker(positionAttribute->IntValue());
								}
								else if(name == "size")
								{
									size = (positionAttribute->IntValue());
								}
								else if(name == "font")
								{
									fontnamn = positionAttribute->Value();
								}
								else if(name == "textboxWidth")
								{
									textbox.x = positionAttribute->IntValue();
								}
								else if(name == "textboxHeight")
								{
									textbox.y = positionAttribute->IntValue();
								}
								else if(name == "emotion")
								{
									emotion = Emotion(positionAttribute->IntValue());
								}
								else if(name == "color")
								{
									if(positionAttribute->Value() == "black")
									{
										color = color.Black;
									}
									if(positionAttribute->Value() == "white")
									{
										color = color.White;
									}
								}
								else if(name == "colorR")
								{
									color.r = positionAttribute->IntValue();
								}
								else if(name == "colorG")
								{
									color.g = positionAttribute->IntValue();
								}
								else if(name == "colorB")
								{
									color.b = positionAttribute->IntValue();
								}
								else if(name == "colorA")
								{
									color.a = positionAttribute->IntValue();
								}
								positionAttribute = positionAttribute->Next();
							}
						}
					}
					root = root->NextSiblingElement("Dialog");
				}
			}
		}
	};
	
	typedef std::vector<sf::Text*> TextVector;
	typedef std::vector<dialogbase*> DialogbaseVector;
	typedef std::map<sf::Text*, Speaker> SpeakerMap;
	typedef std::map<std::string, sf::Font*> fontMap;


public:
	Dialogue();
	~Dialogue();
	static Dialogue* getInstance();
	void update();
	void render();

	void startDialogue(std::string dialogueName);

	bool getendofDialogue();

	bool getStartDialogue()const;
	void setStartDialogue(bool stardDialogue = true);
	
	TextVector textBox(sf::Text &, sf::Vector2f textboxsize, int textsize, std::string fontnamn);

private:
	static Dialogue *sInstance;
	sf::Font& getfont(std::string);
	void playNext();
	void loadDialogue(std::string dialogueName);
	void empthyDialogue();
	void loadText();

	void load(std::string dialogueName);
	TiXmlDocument sDocument;
	
	int currentText;
	int currentLetter;
	int dialogSpeed;
	
	TextVector texts;
	
	SpeakerMap speakerlista;
	
	bool isbuttonpressed;
	bool mEndofDialogue;

	fontMap fonts;
	/*sf::Font *journal_font;
	sf::Font *character_font;*/

	sf::Texture mTexture[4];

	sf::Clock interval;

	bool mStartDialogue;
	
	DialogbaseVector dialogs;
};

#endif