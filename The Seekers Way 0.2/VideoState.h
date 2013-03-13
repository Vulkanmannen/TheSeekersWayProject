#ifndef INCLUDED_VIDEOSTATE
#define INCLUDED_VIDEOSTATE

//#include "SfeMovie\include\sfeMovie\Movie.hpp"
#include "SFML\System.hpp"
#include "State.h"
#include <vector>
#include <string>


class VideoState
{
public:
	VideoState();
	~VideoState();

	void update();
	void render();

	void setVideo(int currentLevel);

private:
	struct Video
	{
		Video(std::string &name, float movieLength, State::MenuStates nextState = State::GameState):
		mMovieLength(movieLength),
		mNextState(nextState)
		{
			//mMovie.openFromFile(name);
		}

		//sfe::Movie mMovie;
		sf::Clock mMovieTimer;
		float mMovieLength;
		State::MenuStates mNextState;
	};

	typedef std::vector<Video*> VideoVector;
	//VideoVector mVideos;

	int mCurrentLevel;
};

#endif