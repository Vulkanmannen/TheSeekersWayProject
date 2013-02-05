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

	void interact(Entity *e);

	sf::Sprite getSprite();
private:
	enum JumpStatus {RIGHT, LEFT, GROUND};

	void wallJump();
	void isWallJumping();
	void canWallJump();
	void hitWall();


	bool mWallJumping;
	bool mCanWallJump;
	bool mCanPressWallJump;
	bool mHitWall;
	bool mFenrirCanJump;
	JumpStatus mLastJumpDir;

	int mWallJumpCount;
	int mWallJumpTime;

};

#endif