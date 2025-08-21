
#include <string>
#include <vector>

struct Coord
{
    int x;
    int y;
};

enum Element
{
    BLANK = 0,  //    0
    WALL = 1,   //    1
    GOAL = 2,   //   10
    BALL = 4,   //  100
    PLAYER = 8, // 1000
    // PLAYER+GOAL 1010    & PLAYER => 1000
};

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Map
{
public:
    Map(int width, int height, int* const map[]);
    ~Map();
    const int width;
    const int height;

    bool Move(Direction direction);
    bool IsCleared() const;

    const int operator()(int x, int y) const;
private:
    int const* const* map;
    Coord player;
    std::vector<Coord> balls;

    bool HasBall(int x, int y) const;
    Coord* GetBall(int x, int y);
};

Map* fromFile(const std::string& filename);

