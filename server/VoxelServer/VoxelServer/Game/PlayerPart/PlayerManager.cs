using System;
using System.Collections.Generic;
using System.Text;

namespace VoxelServer.Game.PlayerPart
{
    class PlayerManager
    {
        Dictionary<int, Player> playerDic=new Dictionary<int, Player>();

        public PlayerManager()
        {
            loadPlayers();
        }
        private void loadPlayers()
        {
            Console.WriteLine(System.IO.Directory.GetCurrentDirectory());

        }
        
    }
}
