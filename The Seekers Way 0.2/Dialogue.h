#ifndef INCLUDED_Dialogue
#define INCLUDED_Dialogue

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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

	int currentText;
	int dialogSpeed;

	sf::Text dialogue;
	
	TextVector texts;
	
	bool isbuttonpressed;
	bool mEndofDialogue;

	sf::Font *journal_font;
	sf::Font *character_font;

	sf::Sprite mSprite;
	sf::Texture mTexture;
};

#endif