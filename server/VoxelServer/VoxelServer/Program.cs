using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using VoxelServer.Game.PlayerPart;
using VoxelServer.Game.WorldPart;

namespace VoxelServer
{
    class Program
    {
        
        
        static void Main(string[] args)
        {
            PlayerManager playerManager = new PlayerManager();
            new WorldManager(playerManager);
        }
        
    }
}
