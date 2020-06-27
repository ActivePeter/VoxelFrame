﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace VoxelServer.Network
{
    class Client
    {
        private Socket clientSocket;
        Server server;
        public const int BUFFER_SIZE = 1024;
        public byte[] buffer = new byte[BUFFER_SIZE];
        public int indexInDic { get; }

        public Client(Server server, Socket clientSocket,int indexInDic)
        {
            this.server = server;
            this.indexInDic = indexInDic;
            this.clientSocket = clientSocket;
            startReceive();
        }
        void startReceive()
        {
            clientSocket.BeginReceive(buffer,0,BUFFER_SIZE, SocketFlags.None, ReceiveCallback,null);
        }
        void handleReceive()
        {

        }
        void ReceiveCallback(IAsyncResult iar)
        {
            try
            {
                if (clientSocket == null || clientSocket.Connected == false) {
                    server.removeClient(this);
                    return;
                } 
                int len = clientSocket.EndReceive(iar);
                Console.WriteLine("接收");
                if (len == 0)
                {
                    Console.WriteLine("接收数据为0");
                    close();
                    return;
                }

                handleReceive();
                startReceive();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                close();
            }
        }
        private void close()
        {
            Console.WriteLine("断开");
            clientSocket.Close();
            server.removeClient(this);
        }
    }
}
