#ifndef INCLUDED_VIDEOSTATE
#define INCLUDED_VIDEOSTATE

#include "SFML\System.hpp"
#include "State.h"
#include <vector>
#include <string>
#include <iostream>
//#include "sfTheora.h"


class VideoState
{
public:
	VideoState();
	~VideoState();

	void update();
	void render();

	void setVideo(int currentLevel);
//	void restartClock();
//
//private:
//	struct Video
//	{
		//Video(std::string &name, float movieLength, State::MenuStates nextState = State::DialogueState):
//		mMovieLength(movieLength),
//		mNextState(nextState)
//		{
//			//mMovie.openFromFile(name);
//			std::cout << "movie name:" << name<< std::endl;
//		}
//
//		sfe::Movie mMovie;	
//		float mMovieLength;
//		State::MenuStates mNextState;
//	};
//
//	typedef std::vector<Video*> VideoVector;
//	VideoVector mVideos;
//
//	sf::Clock mMovieTimer;
//	int mCurrentLevel;

	//sf::Clock mvideoClock;
	//sftheora::Video mVideo;

	//typedef std::vector<sftheora::Video*> VideoVector;
	//VideoVector mVideoVector;
};

#endif