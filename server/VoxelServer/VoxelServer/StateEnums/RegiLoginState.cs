using System;
using System.Collections.Generic;
using System.Text;

namespace VoxelServer.StateEnums
{
    enum RegiState
    {
        Succ=1,
        Exist=2,
        UnknownErr=3
    }

    enum LoginState
    {
        Succ = 1,
        InGame = 2,
        WrongPassOrId=3,
        UnknownErr = 4
    }
}
