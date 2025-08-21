#define _CRT_SECURE_NO_WARNINIGS

#include <iostream>//C++
#include <conio.h>//getch
#include <cmath>//pow제곱함수
#include <Windows.h>//Sleep()
#include <mmsystem.h>
#include <ctime>
#include "Renderer.h"
#include "KeyboardInput.h"
#include "Game.h"

#pragma comment( lib, "winmm.lib")

using namespace std;

/* 전체 정리

Renderer
  ^
Game(움직임 횟수, 전체) - Map(플레이어 움직임, 공 밀기)
  v
KeyboardInput
 */

//메인 그리기 //scolor1 함수 필요//gotoxy1 함수 필요
int mainchoose(const Renderer& renderer)
{
    int mum = 0;
    int put;
    int max = 1;

    while (true)
    {
        renderer.Menu(mum);

        switch (keyInput().meta)
        {
        case ARROW_UP:
            mum--;    //mum
            if (mum < 0) mum = max;
            break;
        case ARROW_DOWN:
            mum++;    //put
            if (mum > max) mum = 0;
            break;
        case ENTER:
            if (mum < max) return mum + 1;
        case ESC:
            return -1;
            break;
        }
    }
}

int main()
{
    Renderer renderer;
    renderer.Init();

    Game game(renderer);

    while (true)
    {
        system("cls");
        int mm = mainchoose(renderer);
        if (mm == 1)
        {
            PlaySound(TEXT("Sound.wav"), NULL, SND_ASYNC | SND_LOOP);
            game.start();
            PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP);
        }//게임시작 끝

        else if (mm == -1)
        {
            break;
        }
    }
    return 0;
}

