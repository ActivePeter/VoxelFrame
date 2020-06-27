using System;
using System.Collections.Generic;
using System.Text;

namespace VoxelServer.Network
{
    class ClientMessageHandler
    {
        public const int BUFFER_SIZE = 1024;
        public byte[] buffer = new byte[BUFFER_SIZE];
        public byte[] previousData;//用来存储之前接收但没接受全的数据
        public void handleReceive(int datalen)
        {
            if (previousData==null)
            {

            }
            else
            {

            }
        }
    }
}
