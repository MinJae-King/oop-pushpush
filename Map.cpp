#include "Map.h"
#include <fstream>
#include <iostream>

using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};

Map::Map(int width, int height, int* const map[]): width(width), height(height)
{
    int** newMap = new int*[height];
    for (int y = 0; y < height; y++)
    {
        newMap[y] = new int[width];
        for (int x = 0; x < width; x++)
        {
            newMap[y][x] = map[y][x];
            // ��Ʈ ������ &�� �̿��ؼ� �ٸ� ��Ʈ�� ���� ���� �÷��̾� ��Ʈ�� �˻�
            if (map[y][x] & PLAYER)
            {
                player.x = x;
                player.y = y;

                // ����: PLAYER�� ��Ʈ ����
                // 1010
                // 1000 -> ~ -> 0111 -> & -> 0010
                // newMap[y][x] &= ~PLAYER;

                // PLAYER ��Ʈ�� ���� �ִٴ� ���� Ȯ���� ���� �׳� ���� ��
                newMap[y][x] -= PLAYER;
            }

            if (map[y][x] & BALL)
            {
                Coord ball;
                ball.x = x;
                ball.y = y;

                newMap[y][x] -= BALL;

                balls.push_back(ball);
            }
        }
    }
    this->map = newMap;
}

Map::~Map()
{
    for (int y = 0; y < height; y++)
    {
        delete[] this->map[y];
    }
    delete[] this->map;
}

bool Map::Move(Direction direction)
{
    int nx = player.x + dx[direction];
    int ny = player.y + dy[direction];

    if (nx < 0 || nx >= width || ny < 0 || ny >= height) return false;
    if (map[ny][nx] & WALL) return false;

    Coord* ball = GetBall(nx, ny);
    if (ball)
    {
        int nnx = ball->x + dx[direction];
        int nny = ball->y + dy[direction];

        if (nnx < 0 || nnx >= width || nny < 0 || nny >= height) return false;
        if (map[nny][nnx] & WALL) return false;
        if (HasBall(nnx, nny)) return false;

        ball->x = nnx;
        ball->y = nny;
    }

    player.x = nx;
    player.y = ny;
    return true;
}

bool Map::IsCleared() const
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((map[y][x] & GOAL) && !HasBall(x, y))
            {
                return false;
            }
        }
    }
    return true;
}

// <- �տ� �ִ� const�� int*�� �پ� �ִ� const
//    �ܺο��� map �����͸� �ٲ� �� ���� ���ִ� const
//     �ڿ� �ִ� const�� �޼��忡 �پ� �ִ� const ->
// �޼��尡 ��ü�� ������� ���� �ٲ��� �ʴ´ٰ� ����ϴ� const
const int Map::operator()(int x, int y) const
{
    int element = map[y][x];
    if (player.x == x && player.y == y)
    {
        //     0010            1000
        // ������ |
        // return map[y][x] | PLAYER;
        // PLAYER ��Ʈ�� ���� �ִٴ� ���� Ȯ���� ���� �׳� ���ص� ��
        element |= PLAYER;
    }
    if (HasBall(x, y))
    {
        element |= BALL;
    }

    return element;
}

bool Map::HasBall(int x, int y) const
{
    for (const Coord& ball : balls)
    {
        if (ball.x == x && ball.y == y)
        {
            return true;
        }
    }
    return false;
}

Coord* Map::GetBall(int x, int y)
{
    for (Coord& ball : balls)
    {
        if (ball.x == x && ball.y == y)
        {
            return &ball;
        }
    }
    return nullptr;
}

Map* fromFile(const std::string& filename)
{
    ifstream in(filename);
    int width, height;
    in >> width >> height;

    int** raw_map = new int* [height];
    for (int y = 0; y < height; y++)
    {
        raw_map[y] = new int[width];
        for (int x = 0; x < width; x++)
        {
            in >> raw_map[y][x];
        }
    }

    Map* map = new Map(width, height, raw_map);

    for (int y = 0; y < height; y++)
    {
        delete[] raw_map[y];
    }
    delete[] raw_map;
    return map;
}
