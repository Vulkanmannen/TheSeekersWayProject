#include "ImageManager.h"
#include "SFML\Graphics.hpp"
#include <map>
#include <cassert>

sf::RenderWindow* ImageManager::sWindow;
std::map<std::string, sf::Image*> ImageManager::sImages;

ImageManager::ImageManager()
	{

	}

ImageManager::~ImageManager()
	{
		for(ImageMap::iterator i = sImages.begin(); i != sImages.end(); ++i)
		{
			delete i->second;
		}
		sImages.clear();
	}

// ritar ut det som skickas in i funktionen i f�nstret
void ImageManager::render(sf::Drawable *drawable, sf::RenderStates states)
{
	sWindow->draw(*drawable, states);
}

// tilldela pekaren ett f�nster
void ImageManager::setWindow(sf::RenderWindow *window)
{
	sWindow = window;
}

// h�mtar den textur som h�r ihop med textstr�ngen
sf::Image* ImageManager::getImage(const std::string &fileName)
{
	sf::Image* image = sImages[fileName];

	if(image == NULL) // om den inte finns s� loadas den
	{
		image = ImageManager::loadImage(fileName);
		sImages[fileName] = image;
	}
	
	return image;
}

// loadar en image 
sf::Image* ImageManager::loadImage(const std::string &fileName)
{
	sf::Image* image = new sf::Image();
	image->loadFromFile("Images/" + fileName);

	assert(image->loadFromFile("Images/" + fileName));

	return image;
}

sf::RenderWindow& ImageManager::getWindow()
{
	return *sWindow;
}

void ImageManager::setFrameRateAndSync(int frameRate, bool verticalSync)
{
	sWindow->setFramerateLimit(frameRate);
	sWindow->setVerticalSyncEnabled(verticalSync);
}