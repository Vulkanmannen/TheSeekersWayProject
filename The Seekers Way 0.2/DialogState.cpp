#include "DialogState.h"
#include "Dialogue.h"

DialogState::DialogState()
{
}


DialogState::~DialogState()
{
}

void DialogState::render()
{
	Dialogue::getInstance()->render();
}

void DialogState::update()
{
	Dialogue::getInstance()->update();
}