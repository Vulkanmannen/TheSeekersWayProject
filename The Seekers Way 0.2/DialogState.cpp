#include "DialogState.h"
#include "Dialogue.h"
#include "State.h"
#include "EntityManager.h"

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
	EntityManager::getInstance()->updateView();
	if(Dialogue::getInstance()->getendofDialogue())
	{
		State::getInstance()->setState(State::GameState);
	}
}