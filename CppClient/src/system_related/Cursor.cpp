#include "Cursor.h"
#if _WIN32 || _WIN64
#include "Cursor_WinAPI.h"
#endif

#include "base/vf_base.h"
// HWND handle;
void Cursor::setLocked(bool locked)
{
    if (locked != this->locked)
    {
        this->locked = locked;
        if (locked)
        {

            lockCursor();
            // ShowCursor(FALSE);
        }
        else
        {
            releaseCursor();
            // ReleaseCapture();

            // ShowCursor(TRUE);
        }
    }
}

// void Cursor::resetCursorPosIfLocked()
// {
//     if(locked){
//         SDL_SetCursorPos
//     }
// }

void Cursor::resetCursorPosIfLocked()
{
    if (locked)
    {
        resetCursorCenter(gameWindow->windowW / 2,
                          gameWindow->windowH / 2);
    }
}

void Cursor::init(GameWindow *gameWindow)
{
    this->gameWindow = gameWindow;
    // handle = GetActiveWindow();

    // setCursorState(true);
}
