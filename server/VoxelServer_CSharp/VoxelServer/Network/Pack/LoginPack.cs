using ProtoBuf;
using System;
using System.Collections.Generic;
using System.Text;

namespace Voxel.Network.Pack
{
    [ProtoContract]
    class LoginRequestPack
    {
        [ProtoMember(1)]
        public int username { get; set; }
        [ProtoMember(2)]
        public string password { get; set; }
    }

    [ProtoContract]
    class LoginResponsePack
    {
        [ProtoMember(1)]
        public LoginState loginState { get; set; }
    }

    enum LoginState
    {
        Succ = 1,
        InGame = 2,
        WrongPassOrId = 3,
        UnknownErr = 4
    }
}
