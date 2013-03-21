#include "VideoState.h"
#include "ImageManager.h"
#include "State.h"
#include "EntityManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"

VideoState::VideoState()
	:mCurrentMovie(0)
{	
	mVideos.push_back(Video("Intro.ogv", 12, State::StartState));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12));
	mVideos.push_back(Video("Intro.ogv", 12, State::StartState));

	mMovie.load(mVideos[mCurrentMovie].mMovie);
}


VideoState::~VideoState()
{

}

void VideoState::update()
{
	mMovie.update(/*mVideoClock.restart()*/sf::seconds(1.0f / 25.0f));

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