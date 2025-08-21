#pragma once

#include "Renderer.h"
#include "KeyboardInput.h"

class ActionQueue;

class Game
{
public:
    Game(Renderer& renderer);
    ~Game();

    void start();
    void ProcessArrowKey(Meta meta, bool track_action, bool is_forward);
private:
    Renderer& renderer;
    ActionQueue* action_queue;

    Map* map = nullptr;
    int lev = 1;
    int rere = 1;
    int step = 0;
    int time = 1000;
    int tt = 0;
};

