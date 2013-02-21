#ifndef INCLUDED_Dialogue
#define INCLUDED_Dialogue

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "tinyxml.h"
#include <map>

class Dialogue
{
public:
	Dialogue();
	~Dialogue();
	static Dialogue* getInstance();
	void update();
	void render();
	void playNext();
	void empthyDialogue();
	void loadDialogue(std::string dialogueName);
	void startDialogue(std::string dialogueName);
	void loadText();
	bool getendofDialogue();
	typedef std::vector<sf::Text*> TextVector;
	TextVector textBox(sf::Text &);

private:
	static Dialogue *sInstance;

	enum Speaker{kiba, charlotte, fenrir, sheeka, journal};
	int currentText;
	int currentLetter;
	int dialogSpeed;
	
	TextVector texts;
	typedef std::map<sf::Text*, Speaker> SpeakerMap;
	SpeakerMap speakerlista;
	
	bool isbuttonpressed;
	bool mEndofDialogue;

	sf::Font *journal_font;
	sf::Font *character_font;

	sf::Sprite mSprite;
	sf::Texture mTexture[4];

	sf::Clock interval;
};

#endif