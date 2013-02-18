#ifndef INCLUDED_FENRIR
#define INCLUDED_FENRIR

#include "Character.h"
#include "SFML\Graphics.hpp"

class Fenrir: public Character
{
public:
	Fenrir(sf::Vector2f &position);
	~Fenrir();
	
	void update(EntityKind &currentEntity);
	void render();

	void onblock();

	void interact(Entity *e);

private:
	enum JumpStatus {RIGHT, LEFT, GROUND};

	void move();
	void takeDamage();
	void fall();

	void wallJump();
	void isWallJumping();
	void canWallJump();
	void updateHitbox();
	bool hitWall();



	bool mWallJumping;
	bool mCanPressWallJump;
	bool mHitWall;
	bool mFenrirCanJump;
	bool mVerticalHitbox;
	bool mWallJumpDirLeft;
	JumpStatus mLastJumpDir;
	sf::Clock mCanHitWallClock;

	int mWallJumpCount;
	int mWallJumpTime;

	// snowmist

	void snowMist();
	void moveInSnowMist();
	void snowMistCountdown();

	bool mCanPressSnowMist;
	bool mInSnowMist;
	bool mCanSnowMist;
	bool mHitVine;
	float mMoveSpeedInMist;
	float mMaxMoveSpeedInMist;

	sf::Clock mSnowMistTime;
};

#endif