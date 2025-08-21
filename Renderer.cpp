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
    "���� ����",
    "���� ����",
};

//���ڿ� ������ �����ϴ� �Լ� // ���ڻ� ��� ���� ������ 15,0
void scolor(unsigned short text = 15, unsigned short back = 0)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

//Ŀ�� ��ġ �̵�
void gotoxy(int x, int y)//windows,stdio
{
    COORD coord = { 0, 0 };
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Renderer::Init() const
{
    // Ŀ�� ������ ����
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = false;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);

    // â ũ�� ����
    system("mode con: cols=50 lines=22");
}

void Renderer::Menu(int selected_row) const
{
    scolor(15, 0);
    gotoxy(MENU_X - 3, MENU_Y + 1);
    cout << "�� ��ü���� ���α׷��� : PushPush *�����* ��";
    
    for (int line = 0; line < 2; line++)
    {
        gotoxy(MENU_X, MENU_Y + 3 + line);
        if (selected_row == line)
        {
            scolor(12, 0);
            cout << "��";
            scolor(15, 0);
        }
        else
        {
            cout << "��";
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
    cout << "E : ���� �ܰ�";
    gotoxy(35, 4);
    cout << "T : ���� �ܰ�";
    gotoxy(35, 5);
    cout << "R : �ٽ� �ϱ� ";
    gotoxy(35, 6);
    cout << "Z : Undo ";
    gotoxy(35, 7);
    cout << "X : Redo ";
    gotoxy(32, 19);
    cout << "������ : �����";
}

void Renderer::DrawStats(int step, int time) const
{
    gotoxy(35, 9);
    cout << "���� : " << step / 100 % 10 << step / 10 % 10 << step % 10;
    gotoxy(35, 10);
    cout << "�ð�   " << time / 600 << (time / 60) % 10 << ":" << time % 60 / 10 << time % 10;
}

void Renderer::DrawNext() const
{
    gotoxy(2, 11);
    cout << "��������������������������������������������������������";
    gotoxy(2, 12);
    cout << "�� ���� �ܰ�� ���� ���Ͻø馭";
    gotoxy(2, 13);
    cout << "��    �ƹ�Ű�� �����ּ��� ! �� ";
    gotoxy(2, 14);
    cout << "��������������������������������������������������������";
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
        cout << "��";
        break;
    case 1:
        scolor(12);
        cout << "��";
        break;
    case 2:
        scolor(2);
        cout << "��";
        break;
    case 3:
        scolor(14);
        cout << "��";
        break;
    case 4:
        scolor(0, 3);
        cout << "��";
        break;
    case 5:
        scolor();
        cout << "  ";
        break;
    }
}

// 1�ʸ��� �� ���� �����
// �߰��� �Է��� ������ �ش� �Է� ó���� �� �ְ� �����
// TODO: �� �� ������ static ���� �Ẹ��
int elapseTime(int& time)
{
    while (_kbhit() == 0) // Ű�� �ƹ��͵� �� ���� ���� �ݺ�
        //kbhit �Լ��� Ű �Է� ���θ� ����. �� ������, �ȴ�����
    {
        if (time <= 0) // ��, �Է��� ������ 0���� �۰ų� ������
            return -1; // -1 ����
        Sleep(10);
        time -= 10;
    }
}
