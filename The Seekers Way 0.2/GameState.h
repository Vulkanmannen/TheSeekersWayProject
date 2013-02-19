#ifndef INCLUDE_GAMESTATE
#define INCLUDE_GAMESTATE
#include "State.h"


class GameState
{
public:
	GameState();
	~GameState();

	void render();
	void update();

};

#endif