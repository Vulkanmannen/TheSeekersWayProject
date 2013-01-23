#include "Animation.h"
#include "ImageManager.h"

Animation::Animation(std::string fileName, int timePerFrame, int numberOfFrames, int height, int width):
	mTimePerFrame(timePerFrame),
	mNumberOfFrames(numberOfFrames),
	mCurrentFrame(0),
	mEndOfAnimation(false),
	mLeftDir(false),
	mTextureRectangle(0, 0, width, height)
	{
		mImage = ImageManager::getImage(fileName); // hämtar textur
		mTexture.loadFromImage(*mImage);
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(mTextureRectangle); // ger spriten rätt storlek
	}

Animation::Animation()
	{}

Animation::~Animation()
	{}

// uppdaterar spriteframen
// kollar om det är dags o byta frame
// byter frame om det är dags
void Animation::update(int rowOfSprite, bool dirLeft)
{
	if(mFrameTimer.getElapsedTime().asMicroseconds() > mTimePerFrame) // kollar om det är dags att byta frame
	{
		mFrameTimer.restart();

		++mCurrentFrame;

		sf::Color color = mImage->getPixel(mTextureRectangle.width * mCurrentFrame, mTextureRectangle.height * rowOfSprite); // hämtar färgen hoss pixeln i det översta hörnet på framen 

		if(mCurrentFrame >= mNumberOfFrames || color == sf::Color(0, 0, 0, 255)) // om färgen e svart så är animationen slut
		{
			mEndOfAnimation = true;
			mCurrentFrame = 0;
		}
		else
		{
			mEndOfAnimation = false;
		}

		mTextureRectangle.left = mTextureRectangle.width * mCurrentFrame; // sätter rutan rätt
		mTextureRectangle.top = mTextureRectangle.height * rowOfSprite;
	
		if(dirLeft && !mLeftDir) // om gubben är vänd åt ena hållet och animationen åt andra hållet så vänds animationen rätt
		{
			mSprite.scale(-1.f, 1.f);
			mLeftDir = true;
		}
		else if(!dirLeft && mLeftDir)
		{
			mSprite.scale(-1.f, 1.f);
			mLeftDir = false;
		}

		mSprite.setTextureRect(mTextureRectangle);
	}
}

// sätter possitionen på spriten
void Animation::setPosition(sf::Vector2f &position)
{
	mSprite.setPosition(position);
}

// returnerar spriten
sf::Sprite Animation::getSprite()const
{
	return mSprite;
}

// returnerar end of animation
bool Animation::getEndOfAnimation()const
{
	return mEndOfAnimation;
}

// sätter animationen att börja från början
void Animation::setAnimationToBegining()
{
	mCurrentFrame = 0;
}