#ifndef INCLUDED_IMAGEMANAGER
#define INCLUDED_IMAGEMANAGER

#include "SFML\Graphics.hpp"

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	static void render(sf::Drawable *drawable);
	static void	setWindow(sf::RenderWindow *window);
private:
	static sf::RenderWindow *sWindow;
};

#endif