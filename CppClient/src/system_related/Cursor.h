#pragma once
//a part of gamewindow

struct GameWindow;
//
class Cursor
{
private:
    bool locked;

public:
    GameWindow *gameWindow;
    double cursorX;
    double cursorY;
    /**
     * locked getter & setter
    */
    void setLocked(bool locked);
    inline bool getLocked()
    {
        return locked;
    }

    void resetCursorPosIfLocked();
    // Cursor();
    void init(GameWindow *gameWindow);
};
#include "GameWindow.h"