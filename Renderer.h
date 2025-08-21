#pragma once

#include "Map.h"


class Renderer
{
public:
    void Init() const;
    void Menu(int mum) const;
    void Draw(const Map& map);
    void DrawInfo(int level) const;
    void DrawStats(int step, int time) const;
    void DrawNext() const;
    void ClearNext() const;
    void ClearCache();

private:
    int** cache = nullptr;
    int cache_width;
    int cache_height;

    void CreateCache(int width, int height);
    void Draw(int x, int y, int type);
};

int elapseTime(int& milliseconds);
