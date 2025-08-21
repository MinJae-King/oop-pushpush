#include "Game.h"
#include "Renderer.h"
#include "KeyboardInput.h"
#include "ActionQueue.h"
#include <conio.h>
#include <string>

using namespace std;

const string MAPS[] =
{
    "map01.梯團營",
    "map02.梯團營",
    "map03.梯團營",
    "map04.梯團營",
    "map05.梯團營",
};

Game::Game(Renderer& renderer): renderer(renderer)
{
    action_queue = new ActionQueue(*this);
}

Game::~Game()
{
    delete action_queue;
}

void Game::start()
{
    system("cls");
    renderer.ClearCache();
    lev = 1;
    rere = 1;
    step = 0;
    time = 1000;
    tt = 0;

    while (true)
    {

        if (rere == 1)
        {
            if (map) delete map;
            map = fromFile(MAPS[lev - 1]);
            rere = 0;

            renderer.DrawInfo(lev);
            action_queue->Clear();
            step = 0;
        }

        renderer.Draw(*map);
        renderer.DrawStats(step, tt);

        elapseTime(time);
        if (time <= 0) time = 1000, tt++;

        if (_kbhit())
        {
            Key key = keyInput();
            if (key.isMeta)
            {
                ProcessArrowKey(key.meta, true, true);
                if (key.meta == ESC) break;
            }
            else
            {
                switch (key.alpha)
                {
                case 'e':
                case 'E':
                    if (--lev < 1) lev = 1;
                    rere = 1;
                    break;
                case 't':
                case 'T':
                    if (++lev > 5) lev = 5;
                    rere = 1;
                    break;
                case 'r':
                case 'R':
                    rere = 1;
                    break;
                case 'z':
                case 'Z':
                    action_queue->Undo();
                    break;
                case 'x':
                case 'X':
                    action_queue->Redo();
                    break;
                }
            }
        }

        if (map->IsCleared())
        {
            lev++, rere++;

            renderer.Draw(*map);
            renderer.DrawNext();
            keyInput();
            renderer.ClearNext();
        }
    }
}

void Game::ProcessArrowKey(Meta meta, bool track_action, bool is_forward)
{
    bool success = false;
    switch (meta)
    {
    case ARROW_UP:
        success = map->Move(UP);
        break;
    case ARROW_DOWN:
        success = map->Move(DOWN);
        break;
    case ARROW_RIGHT:
        success = map->Move(RIGHT);
        break;
    case ARROW_LEFT:
        success = map->Move(LEFT);
        break;
    }

    if (success)
    {
        if (is_forward)
        {
            step++;
        }
        else
        {
            step--;
        }

        if (track_action)
        {
            action_queue->Action(meta);
        }
    }
}
