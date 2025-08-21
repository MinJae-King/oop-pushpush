#pragma once

#include <stack>
#include "KeyboardInput.h"

class Game;

class ActionQueue
{
public:
	ActionQueue(Game& game);
	void Action(Meta meta);
	void Undo();
	void Redo();
	void Clear();
private:
	Game& game;
	std::stack<Meta> history;
	std::stack<Meta> future;
};

