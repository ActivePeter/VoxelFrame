using ProtoBuf;
using System;
using System.Collections.Generic;
using System.Text;

namespace Voxel.Network.Pack
{
    [ProtoContract]
    class RegiRequestPack
    {
        [ProtoMember(1)]
        public int username { get; set; }
        [ProtoMember(2)]
        public string password { get; set; }
    }

    [ProtoContract]
    class RegiResponsePack
    {
        [ProtoMember(1)]
        public RegiState regiState { get; set; }
    }

    enum RegiState
    {
        Succ = 1,
        Exist = 2,
        UnknownErr = 3
    }
}
