#pragma once
#include "_media_api.h"
#include "Windows.h"
inline void lockCursor()
{
    SDL_ShowCursor(false);
    auto handle = GetActiveWindow();
    RECT wr;
    GetWindowRect(handle, &wr);
    wr.top += 100;
    wr.bottom -= 100;
    wr.left += 100;
    wr.right -= 100;
    ClipCursor(&wr);
}
inline void releaseCursor()
{
    SDL_ShowCursor(true);
    ClipCursor(NULL);
}
inline void resetCursorCenter(int x, int y)
{
    auto handle = GetActiveWindow();
    // LPPOINT p;
    POINT point;
    point.x = x;
    point.y = y;
    ClientToScreen(handle, &point);

    // RECT r;
    // GetClientRect(handle, &r);
    // printf("win rect %d %d\r\n", r.top, r.left);
    // printf("win rect %d %d\r\n", point.x, point.y);
    // x = point.x;
    // y = point.y;
    SetCursorPos(point.x, point.y);
}