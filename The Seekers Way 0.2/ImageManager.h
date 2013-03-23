#ifndef INCLUDED_IMAGEMANAGER
#define INCLUDED_IMAGEMANAGER

#include "SFML\Graphics.hpp"
#include <map>
#include <string>

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	static void render(sf::Drawable *drawable, sf::RenderStates states = sf::RenderStates::Default);

	static sf::Image* getImage(const std::string &fileName);

	static void	setWindow(sf::RenderWindow *window);
	static sf::RenderWindow& getWindow();

	static void setFrameRateAndSync(int frameRate, bool verticalSync);
private:
	static sf::RenderWindow *sWindow;

	static sf::Image* loadImage(const std::string &fileName);
	typedef std::map<std::string, sf::Image*> ImageMap;
	static ImageMap sImages;
};

#endif