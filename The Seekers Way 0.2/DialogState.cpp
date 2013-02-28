#include "DialogState.h"
#include "Dialogue.h"
#include "State.h"
#include "EntityManager.h"
#include "LevelManager.h"

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
		if(Dialogue::getInstance()->getStartDialogue())
		{
			State::getInstance()->setState(State::GameState);
		}
		else
		{
			LevelManager::getInstance()->LoadLevel(LevelManager::getInstance()->getCurrentLevel() + 1);
		}
	}
}