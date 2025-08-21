#define _CRT_SECURE_NO_WARNINIGS

#include <iostream>//C++
#include <conio.h>//getch
#include <cmath>//pow�����Լ�
#include <Windows.h>//Sleep()
#include <mmsystem.h>
#include <ctime>
#include "Renderer.h"
#include "KeyboardInput.h"
#include "Game.h"

#pragma comment( lib, "winmm.lib")

using namespace std;

/* ��ü ����

Renderer
  ^
Game(������ Ƚ��, ��ü) - Map(�÷��̾� ������, �� �б�)
  v
KeyboardInput
 */

//���� �׸��� //scolor1 �Լ� �ʿ�//gotoxy1 �Լ� �ʿ�
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
        }//���ӽ��� ��

        else if (mm == -1)
        {
            break;
        }
    }
    return 0;
}

