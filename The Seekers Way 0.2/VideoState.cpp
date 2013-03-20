#include "VideoState.h"
#include "ImageManager.h"
#include "State.h"
#include "EntityManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"

VideoState::VideoState()
	//:mCurrentLevel(0)
{
	/*mVideos.push_back(new Video(std::string("Kim_1.wmv"), 8));
	mVideos.push_back(new Video(std::string("Kim_1.wmv"), 8));
	mVideos.push_back(new Video(std::string("Kim_1.wmv"), 8));
	mVideos.push_back(new Video(std::string("Kim_1.wmv"), 8));
	mVideos.push_back(new Video(std::string("Kim_1.wmv"), 8, State::StartState));*/
}


VideoState::~VideoState()
{
	//while(!mVideos.empty())
	//{
	//	mVideos.pop_back();
	//}
}
//
void VideoState::update()
{
	//if(mMovieTimer.getElapsedTime().asSeconds() > mVideos[mCurrentLevel]->mMovieLength)
	//{
		//LevelManager::getInstance()->lastMovie();
		//State::getInstance()->setState(mVideos[mCurrentLevel]->mNextState);
	//	
	//}
}

void VideoState::render()
{
	//ImageManager::render(&mVideos[mCurrentLevel]->mMovie);
}
//
//void VideoState::setVideo(int currentLevel)
//{
//	mCurrentLevel = currentLevel;
//	mVideos[mCurrentLevel]->mMovie.play();
//	mVideos[mCurrentLevel]->mMovie.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
//}
//
//void VideoState::restartClock()
//{
//	mMovieTimer.restart();
//}