#include "StartMenu.h"
#include "ImageManager.h"
#include "Animation.h"


StartMenu::StartMenu()
{
	mTexture.loadFromFile(*ImageManager::getImage("StartMenu.png"));
}


StartMenu::~StartMenu()
{
}

void StartMenu::update()
{
	
}

void StartMenu::render()
{

}