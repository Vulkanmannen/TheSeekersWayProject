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
	void updateSatatus();
	bool hitWall();

	// walljump

	bool mWallJumping;
	bool mCanPressWallJump;
	bool mHitWall;
	bool mFenrirCanJump;
	bool mVerticalHitbox;
	bool mWallJumpDirLeft;
	JumpStatus mLastJumpDir;
	sf::Clock mCanHitWallClock;
	void falling();

	int mWallJumpCount;
	int mWallJumpTime;

	bool mFallFenrir;

	// snowmist

	void snowMist();
	void notInSnowMist();
	void moveInSnowMist();
	void snowMistCountdown(EntityKind &currentEntity);

	bool mCanPressSnowMist;
	bool mInSnowMist;
	bool mCanSnowMist;
	bool mHitVine;
	float mMoveSpeedInMist;
	float mMaxMoveSpeedInMist;

	sf::Clock mSnowMistTime;
};

#endif