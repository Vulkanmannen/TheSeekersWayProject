#ifndef INCLUDED_VIDEOSTATE
#define INCLUDED_VIDEOSTATE

#include "SFML\System.hpp"
#include "State.h"
#include <vector>
#include <string>
#include <iostream>
#include "sfTheora.h"


class VideoState
{
public:
	VideoState();
	~VideoState();

	void update();
	void render();

	void newMovie(int currentMovie);

private:
	struct Video
	{
		Video(std::string name, float movieLength, State::MenuStates nextState = State::DialogueState):
		mMovieLength(movieLength),
		mNextState(nextState),
		mMovie(name)
		{}

		std::string mMovie;	
		float mMovieLength;
		State::MenuStates mNextState;
	};

	sf::Clock mVideoClock;
	void restartClock();
	sftheora::Video	mMovie;

	typedef std::vector<Video> VideoVector;
	VideoVector mVideos;

	sf::Clock mMovieTimer;
	int mCurrentMovie;
	bool mStartingMovie;
	bool mNextMovie;
	void setVideo();
};

#endif