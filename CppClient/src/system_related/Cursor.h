#pragma once
//a part of gamewindow

struct GameWindow;
//
struct Cursor
{
    GameWindow *gameWindow;
    bool locked;
    double cursorX;
    double cursorY;
    void setCursorState(bool locked);
    void resetCursorPosIfLocked();
    // Cursor();
    void init(GameWindow *gameWindow);
};
#include "GameWindow.h"