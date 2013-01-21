#include "ImageManager.h"
#include "SFML\Graphics.hpp"

sf::RenderWindow* ImageManager::sWindow;

ImageManager::ImageManager()
	{}


ImageManager::~ImageManager()
	{}

// ritar ut det som skickas in i funktionen i fönstret
void ImageManager::render(sf::Drawable *drawable)
{
	sWindow->draw(*drawable);
}

// tilldela pekaren ett fönster
void ImageManager::setWindow(sf::RenderWindow *window)
{
	sWindow = window;
}

