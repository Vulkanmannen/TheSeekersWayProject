#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include <string>

class Animation
{
public:
	Animation(std::string fileName, int timePerFrame, int numberOfFrames, int height, int width);
	Animation();
	~Animation();

	void update(int rowOfSprite);
	void setPosition(sf::Vector2f &position);
	sf::Sprite getSprite()const;
	bool getEndOfAnimation()const;
	void setAnimationToBegining();

private:
	int mNumberOfFrames;
	int mTimePerFrame;
	int mCurrentFrame;
	int mLastRow;
	bool mEndOfAnimation;
	bool mLeftDir;
	sf::Clock mFrameTimer;
	sf::Image *mImage;
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::IntRect mTextureRectangle;
};

#endif