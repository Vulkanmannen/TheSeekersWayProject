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
		mImage = ImageManager::getImage(fileName); // h�mtar textur
		mTexture.loadFromImage(*mImage);
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(mTextureRectangle); // ger spriten r�tt storlek
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
	
	mImage = ImageManager::getImage(fileName); // h�mtar textur
	mTexture.loadFromImage(*mImage);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(mTextureRectangle); // ger spriten r�tt storlek
}

// uppdaterar spriteframen
// kollar om det �r dags o byta frame
// byter frame om det �r dags
void Animation::update(int rowOfSprite)
{
	if(mFrameTimer.getElapsedTime().asMilliseconds() > mTimePerFrame) // kollar om det �r dags att byta frame
	{
		mFrameTimer.restart();

		if(mLastRow == rowOfSprite)
		{
			++mCurrentFrame;

			sf::Color color = mImage->getPixel(mTextureRectangle.width * mCurrentFrame, mTextureRectangle.height * rowOfSprite); // h�mtar f�rgen hoss pixeln i det �versta h�rnet p� framen 

			if(mCurrentFrame >= mNumberOfFrames || color == sf::Color(0, 255, 0, 255)) // om f�rgen e svart s� �r animationen slut
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

		mTextureRectangle.left = mTextureRectangle.width * mCurrentFrame; // s�tter rutan r�tt
		mTextureRectangle.top = mTextureRectangle.height * rowOfSprite;
		mSprite.setTextureRect(mTextureRectangle);

		mLastRow = rowOfSprite;
	}
}

// s�tter possitionen p� spriten
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

// s�tter animationen att b�rja fr�n b�rjan
void Animation::setAnimationToBegining()
{
	mCurrentFrame = 0;
}

void Animation::RotateAnimation(float angle)
{
	mSprite.setOrigin(32 + 64 * mCurrentFrame, 32);
	mSprite.rotate(angle);
}
