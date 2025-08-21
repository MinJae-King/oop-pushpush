#include "KeyboardInput.h"
#include <conio.h>//getch

Key keyInput()
{
    Key key;
    int value = _getch();
    switch (value)
    {
    case 224:
        key.isMeta = true;
        switch (_getch())
        {
        case 80:
            key.meta = ARROW_DOWN;
            break;
        case 75:
            key.meta = ARROW_LEFT;
            break;
        case 72:
            key.meta = ARROW_UP;
            break;
        case 77:
            key.meta = ARROW_RIGHT;
            break;
        }
        break;
    case 27:
        key.isMeta = true;
        key.meta = ESC;
        break;
    case 13:
        key.isMeta = true;
        key.meta = ENTER;
        break;
    default:
        key.isMeta = false;
        key.alpha = value;
        break;
    }
    return key;
}
