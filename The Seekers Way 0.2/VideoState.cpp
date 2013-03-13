#include "VideoState.h"


VideoState::VideoState():
	mCurrentLevel(0)
{
	//mVideos.push_back(new Video(std::string("Kim_1"), 120));
}


VideoState::~VideoState()
{
	//while(!mVideos.empty())
	//{
	//	mVideos.pop_back();
	//}
}

void VideoState::update()
{

}

void VideoState::render()
{
	
}

void VideoState::setVideo(int currentLevel)
{
	mCurrentLevel = currentLevel;
}
