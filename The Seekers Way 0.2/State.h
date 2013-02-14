#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"


class State
{
public:
	State();

	void render();
	void update();

	~State();
};
#endif