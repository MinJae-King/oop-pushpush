#include "ActionQueue.h"
#include "Game.h"

ActionQueue::ActionQueue(Game& game) : game(game)
{
}

void ActionQueue::Action(Meta meta)
{
	history.push(meta);
	while (!future.empty()) future.pop();
}

void ActionQueue::Undo()
{
	if (history.empty()) return;

	Meta meta = history.top();
	history.pop();

	game.ProcessArrowKey((Meta)(7 - meta), false, false);

	future.push(meta);
}

void ActionQueue::Redo()
{
	if (future.empty()) return;

	Meta meta = future.top();
	future.pop();

	game.ProcessArrowKey(meta, false, true);

	history.push(meta);
}

void ActionQueue::Clear()
{
	while (!history.empty()) history.pop();
	while (!future.empty()) future.pop();
}