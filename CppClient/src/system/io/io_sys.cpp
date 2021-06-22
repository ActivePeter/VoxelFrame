#include "io_sys.h"
#include "Windows.h"

namespace N_IO
{
    void setCursorPos(int x, int y)
    {
        SetCursorPos(x, y);
    }

}