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
	std::string getMusic(int movie)const;

private:
	struct Video
	{
		Video(std::string name, std::string music, State::MenuStates nextState = State::DialogueState):
		mNextState(nextState),
		mMovie(name),
		mMusic(music)
		{}

		std::string mMovie;
		std::string mMusic;

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