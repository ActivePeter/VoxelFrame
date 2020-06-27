using System;
using System.Collections.Generic;
using System.Text;

namespace VoxelServer.Network
{
    class ClientMessageHandler
    {
        public const int BUFFER_SIZE = 1024;
        public byte[] buffer = new byte[BUFFER_SIZE];
        public void handleReceive()
        {

        }
    }
}
