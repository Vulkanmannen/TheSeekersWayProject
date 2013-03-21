#include "VideoState.h"
#include "ImageManager.h"
#include "State.h"
#include "EntityManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"

VideoState::VideoState()
	:mCurrentMovie(0)
{	
	mVideos.push_back(Video("splashscreen.ogv", 12, State::StartState));
	mVideos.push_back(Video("intro.ogv", 75));
	mVideos.push_back(Video("TransitionKC.ogv", 6));
	mVideos.push_back(Video("TransitionMEET.ogv", 9.5));
	mVideos.push_back(Video("Transition.ogv", 6));
	mVideos.push_back(Video("Transition.ogv", 6));
	mVideos.push_back(Video("Transition.ogv", 6));
	mVideos.push_back(Video("Transition.ogv", 6));
	mVideos.push_back(Video("Transition.ogv", 6, State::StartState));

	mMovie.load(mVideos[mCurrentMovie].mMovie);
}


VideoState::~VideoState()
{

}

void VideoState::update()
{
	mMovie.update(mVideoClock.restart()/*sf::seconds(1.0f / 26.0f)*/);

	if(mStartingMovie)
	{
		setVideo();
	}

	if((mMovieTimer.getElapsedTime().asSeconds() > mVideos[mCurrentMovie].mMovieLength && mNextMovie) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		State::getInstance()->setState(mVideos[mCurrentMovie].mNextState);	
		mMovie.stop();
		mNextMovie = false;
	}
}

void VideoState::render()
{
	if(!mStartingMovie)
	{
		ImageManager::render(&mMovie);
	}
}

void VideoState::setVideo()
{
	mStartingMovie = false;
	mMovie.load(mVideos[mCurrentMovie].mMovie);
	mMovie.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
	mMovie.play();
	restartClock();
	mNextMovie = true;

	if(mCurrentMovie > mVideos.size() - 1)
	{
		mCurrentMovie = 1;
	}
}

void VideoState::restartClock()
{
	mMovieTimer.restart();
}

void VideoState::newMovie(int currentMovie)
{
	mCurrentMovie = currentMovie;
	mStartingMovie = true;
}
