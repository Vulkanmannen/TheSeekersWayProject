#ifndef INCLUDED_Dialogue
#define INCLUDED_Dialogue

#include <SFML/Graphics.hpp>


class Dialogue
{
public:
	Dialogue();
	~Dialogue();
	static Dialogue* getInstance();
	void update();
	void render();
	void setWindow(sf::RenderWindow *window);

private:
	static Dialogue *sInstance;
	int dialogSpeed;
	sf::Text text;
	sf::RenderWindow *dWindow;
};

#endif