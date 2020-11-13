using Apex.Serialization.Attributes;
using ProtoBuf;
using System;
using System.Collections.Generic;
using System.Text;

namespace Voxel.Network.Pack
{
    class PackHandler
    {
        public void deserializePack(int packId,System.IO.Stream stream)
        {
            switch ((PackId)packId)
            {
                case PackId.LoginRequest:
                    LoginRequestPack loginRequestPack= Serializer.Deserialize<LoginRequestPack>(stream);
                    break;
                case PackId.LoginResponse:
                    LoginResponsePack loginResponsePack = Serializer.Deserialize<LoginResponsePack>(stream);
                    break;
                case PackId.RegiRequest:
                    RegiRequestPack regiRequestPack = Serializer.Deserialize<RegiRequestPack>(stream);
                    break;
                case PackId.RegiResponse:
                    RegiResponsePack regiResponsePack = Serializer.Deserialize<RegiResponsePack>(stream);
                    break;
            }
        }
        //public PackId serializePack()
        //{
        //    Serializer.Serialize()
        //}

    }


    enum PackId
    {
        RegiResponse = 0,
        RegiRequest = 1,
        LoginResponse = 2,
        LoginRequest = 3,
    }
}
