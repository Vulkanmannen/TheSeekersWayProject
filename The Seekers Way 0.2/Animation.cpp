#include "Animation.h"
#include "ImageManager.h"

Animation::Animation(std::string fileName, int timePerFrame, int numberOfFrames, int height, int width):
	mTimePerFrame(timePerFrame),
	mNumberOfFrames(numberOfFrames),
	mCurrentFrame(0),
	mEndOfAnimation(false),
	mLeftDir(false),
	mLastRow(0),
	mTextureRectangle(0, 0, width, height)
	{
		mImage = ImageManager::getImage(fileName); // hämtar textur
		mTexture.loadFromImage(*mImage);
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(mTextureRectangle); // ger spriten rätt storlek
	}

Animation::Animation(int height, int width):
	mTextureRectangle(0, 0, width, height)
	{}

Animation::~Animation()
	{}

void Animation::init(std::string fileName, int timePerFrame, int numberOfFrames)
{
	mTimePerFrame		= timePerFrame;
	mNumberOfFrames		= numberOfFrames;
	mCurrentFrame		= 0;
	mEndOfAnimation		= false;
	mLeftDir			= false;
	mLastRow			= 0;
	
	mImage = ImageManager::getImage(fileName); // hämtar textur
	mTexture.loadFromImage(*mImage);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(mTextureRectangle); // ger spriten rätt storlek
}

// uppdaterar spriteframen
// kollar om det är dags o byta frame
// byter frame om det är dags
void Animation::update(int rowOfSprite)
{
	if(mFrameTimer.getElapsedTime().asMilliseconds() > mTimePerFrame) // kollar om det är dags att byta frame
	{
		mFrameTimer.restart();

		if(mLastRow == rowOfSprite)
		{
			++mCurrentFrame;

			sf::Color color = mImage->getPixel(mTextureRectangle.width * mCurrentFrame, mTextureRectangle.height * rowOfSprite); // hämtar färgen hoss pixeln i det översta hörnet på framen 

			if(mCurrentFrame >= mNumberOfFrames || color == sf::Color(0, 255, 0, 255)) // om färgen e svart så är animationen slut
			{
				mEndOfAnimation = true;
				mCurrentFrame = 0;
			}
			else if(color == sf::Color(0, 0, 255, 255))
			{
				mEndOfAnimation = true;
				--mCurrentFrame;
			}
			else
			{
				mEndOfAnimation = false;
			}
		}
		else
		{
			mCurrentFrame = 0;
			mEndOfAnimation = false;
		}

		mTextureRectangle.left = mTextureRectangle.width * mCurrentFrame; // sätter rutan rätt
		mTextureRectangle.top = mTextureRectangle.height * rowOfSprite;
		mSprite.setTextureRect(mTextureRectangle);

		mLastRow = rowOfSprite;
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

void Animation::RotateAnimation(float angle)
{
	mSprite.setOrigin(32 + 64 * mCurrentFrame, 32);
	mSprite.rotate(angle);
}
