#include "ImageManager.h"
#include "SFML\Graphics.hpp"

sf::RenderWindow* ImageManager::sWindow;

ImageManager::ImageManager()
	{}


ImageManager::~ImageManager()
	{}

// ritar ut det som skickas in i funktionen i f�nstret
void ImageManager::render(sf::Drawable *drawable)
{
	sWindow->draw(*drawable);
}

// tilldela pekaren ett f�nster
void ImageManager::setWindow(sf::RenderWindow *window)
{
	sWindow = window;
}

