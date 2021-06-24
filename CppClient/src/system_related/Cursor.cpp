#include "Cursor.h"
#include "Windows.h"
#include "base.h"
HWND handle;
void Cursor::setLocked(bool locked)
{
    if (locked != this->locked)
    {
        this->locked = locked;
        if (locked)
        {
            // auto handle = GetActiveWindow();
            RECT wr;
            GetWindowRect(handle, &wr);
            wr.top += 100;
            wr.bottom -= 100;
            wr.left += 100;
            wr.right -= 100;
            ClipCursor(&wr);
            ShowCursor(FALSE);
        }
        else
        {
            // ReleaseCapture();
            ClipCursor(NULL);
            ShowCursor(TRUE);
        }
    }
}

void Cursor::resetCursorPosIfLocked()
{
    if (locked)
    {
        // handle = GetActiveWindow();
        // LPPOINT p;
        POINT point;
        point.x = gameWindow->windowW / 2;
        point.y = gameWindow->windowH / 2;
        ClientToScreen(handle, &point);

        // RECT r;
        // GetClientRect(handle, &r);
        // printf("win rect %d %d\r\n", r.top, r.left);
        printf("win rect %d %d\r\n", point.x, point.y);
        // x = point.x;
        // y = point.y;
        SetCursorPos(point.x, point.y);
    }
}

void Cursor::init(GameWindow *gameWindow)
{
    this->gameWindow = gameWindow;
    handle = GetActiveWindow();

    // setCursorState(true);
}
