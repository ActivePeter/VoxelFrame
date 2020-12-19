using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace VoxelServer.Network
{
    class Server
    {
        private static Socket socket;
        Dictionary<int, Client> clients=new Dictionary<int, Client>();
        int latestIndex = 0;
        List<int> removedIndexes = new List<int>();

        public Server(int port)
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Bind(new IPEndPoint(IPAddress.Parse("127.0.0.1"), port));
            socket.Listen(0);
        }
        void startAccept()
        {
            socket.BeginAccept(acceptCallBack, null);
        }
        void acceptCallBack(IAsyncResult iar)
        {
            Socket clientSocket = socket.EndAccept(iar);
            if (removedIndexes.Count > 0)
            {
                int index = removedIndexes[0];
                removedIndexes.RemoveAt(0);
                clients.Add(index, new Client(this,clientSocket, index));
            }
            else
            {
                clients.Add(latestIndex, new Client(this,clientSocket, latestIndex));
                latestIndex++;
            }
        }
        public void removeClient(Client client)
        {
            clients.Remove(client.indexInDic);
            removedIndexes.Add(client.indexInDic);
        }
    }
}
