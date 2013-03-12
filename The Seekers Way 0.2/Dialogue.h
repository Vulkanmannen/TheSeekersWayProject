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
		}
		sf::Vector2f	textposition;
		sf::Vector2f	bildposition;
		sf::Vector2f	textbox;
		sf::Text		text;
		std::string		bildnamn;
		std::string		fontnamn;
		float			size;
		Emotion			emotion;
		Speaker			speaker;
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
	
	TextVector textBox(sf::Text &, sf::Vector2f textboxsize, int textsize);

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
	sf::Font *journal_font;
	sf::Font *character_font;

	sf::Sprite mSprite;
	sf::Texture mTexture[4];

	sf::Clock interval;

	bool mStartDialogue;
	
	DialogbaseVector dialogs;
};

#endif