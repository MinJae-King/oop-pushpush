#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

enum Meta
{
    ESC,
    ENTER,
    ARROW_UP,
    ARROW_RIGHT,
    ARROW_LEFT,
    ARROW_DOWN,
};

struct Key
{
    bool isMeta;
    union
    {
        Meta meta;
        char alpha;
    };
};

Key keyInput();

#endif // KEYBOARDINPUT_H
