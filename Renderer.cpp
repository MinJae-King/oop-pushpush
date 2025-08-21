#include "Renderer.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>//getch

using namespace std;

const int MENU_X = 5;
const int MENU_Y = 3;
const string MENUS[] =
{
    "게임 시작",
    "게임 종료",
};

//글자와 바탕색 설정하는 함수 // 글자색 흰색 바탕 검은색 15,0
void scolor(unsigned short text = 15, unsigned short back = 0)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

//커서 위치 이동
void gotoxy(int x, int y)//windows,stdio
{
    COORD coord = { 0, 0 };
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Renderer::Init() const
{
    // 커서 깜빡임 삭제
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = false;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);

    // 창 크기 조절
    system("mode con: cols=50 lines=22");
}

void Renderer::Menu(int selected_row) const
{
    scolor(15, 0);
    gotoxy(MENU_X - 3, MENU_Y + 1);
    cout << "★ 객체지향 프로그래밍 : PushPush *김민재* ★";
    
    for (int line = 0; line < 2; line++)
    {
        gotoxy(MENU_X, MENU_Y + 3 + line);
        if (selected_row == line)
        {
            scolor(12, 0);
            cout << "▶";
            scolor(15, 0);
        }
        else
        {
            cout << "▷";
        }
        cout << "   " << MENUS[line];
    }
}

void Renderer::Draw(const Map& map)
{
    CreateCache(map.width, map.height);

    gotoxy(0, 0);
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            gotoxy(x * 2 + 2, y + 1);

            int element = map(x, y);
            int type = 5;
            if (element & PLAYER)
            {
                type = 0;
            }
            else if (element & BALL && element & GOAL)
            {
                type = 1;
            }
            else if (element & BALL)
            {
                type = 2;
            }
            else if (element & GOAL)
            {
                type = 3;
            }
            else if (element & WALL)
            {
                type = 4;
            }
            Draw(x, y, type);
        }
    }
    scolor();
}

void Renderer::DrawInfo(int level) const
{
    gotoxy(35, 1);
    cout << "STAGE " << level / 100 << level / 10 % 10 << level % 10;
    gotoxy(35, 3);
    cout << "E : 이전 단계";
    gotoxy(35, 4);
    cout << "T : 다음 단계";
    gotoxy(35, 5);
    cout << "R : 다시 하기 ";
    gotoxy(35, 6);
    cout << "Z : Undo ";
    gotoxy(35, 7);
    cout << "X : Redo ";
    gotoxy(32, 19);
    cout << "개발자 : 김민재";
}

void Renderer::DrawStats(int step, int time) const
{
    gotoxy(35, 9);
    cout << "걸음 : " << step / 100 % 10 << step / 10 % 10 << step % 10;
    gotoxy(35, 10);
    cout << "시간   " << time / 600 << (time / 60) % 10 << ":" << time % 60 / 10 << time % 10;
}

void Renderer::DrawNext() const
{
    gotoxy(2, 11);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    gotoxy(2, 12);
    cout << "┃ 다음 단계로 가길 원하시면┃";
    gotoxy(2, 13);
    cout << "┃    아무키나 눌러주세요 ! ┃ ";
    gotoxy(2, 14);
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
}

void Renderer::ClearNext() const
{
    gotoxy(2, 11);
    cout << "                              ";
    gotoxy(2, 12);
    cout << "                              ";
    gotoxy(2, 13);
    cout << "                              ";
    gotoxy(2, 14);
    cout << "                              ";
}

void Renderer::ClearCache()
{
    if (!cache) return;
    for (int y = 0; y < cache_height; y++)
    {
        for (int x = 0; x < cache_width; x++)
        {
            cache[y][x] = -1;
        }
    }
}

void Renderer::CreateCache(int width, int height)
{
    if (width == cache_width && height == cache_height)
    {
        return;
    }

    if (cache)
    {
        for (int i = 0; i < cache_height; i++)
        {
            delete[] cache[i];
        }
        delete[] cache;
    }

    cache_width = width;
    cache_height = height;
    cache = new int* [height];
    for (int i = 0; i < height; i++)
    {
        cache[i] = new int[width];
    }
    ClearCache();
}

void Renderer::Draw(int x, int y, int type)
{
    if (x < 0 || x >= cache_width ||
        y < 0 || y >= cache_height ||
        cache[y][x] == type) return;

    cache[y][x] = type;
    switch (type)
    {
    case 0:
        scolor(5);
        cout << "★";
        break;
    case 1:
        scolor(12);
        cout << "●";
        break;
    case 2:
        scolor(2);
        cout << "◎";
        break;
    case 3:
        scolor(14);
        cout << "●";
        break;
    case 4:
        scolor(0, 3);
        cout << "▣";
        break;
    case 5:
        scolor();
        cout << "  ";
        break;
    }
}

// 1초마다 한 번씩 종료됨
// 중간에 입력이 있으면 해당 입력 처리할 수 있게 종료됨
// TODO: 할 수 있으면 static 변수 써보기
int elapseTime(int& time)
{
    while (_kbhit() == 0) // 키가 아무것도 안 눌린 동안 반복
        //kbhit 함수는 키 입력 여부를 조사. 즉 눌렀나, 안눌렀나
    {
        if (time <= 0) // 즉, 입력이 없으면 0보다 작거나 같으면
            return -1; // -1 리턴
        Sleep(10);
        time -= 10;
    }
}
