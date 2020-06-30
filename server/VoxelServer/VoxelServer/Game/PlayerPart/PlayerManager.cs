using System;
using System.Collections.Generic;
using System.Text;
using VoxelServer.Utils;

namespace VoxelServer.Game.PlayerPart
{
    class PlayerManager
    {
        public static PlayerManager instance;
        Dictionary<int, Player> playerDic=new Dictionary<int, Player>();

        public PlayerManager()
        {
            instance = this;
            loadPlayers();
        }
        private void loadPlayers()
        {
            //Console.WriteLine(System.IO.Directory.GetCurrentDirectory());
            FileUtils.createIfNotExist("data");
            FileUtils.createIfNotExist("data/playerData");
            
        }
        
    }
}
