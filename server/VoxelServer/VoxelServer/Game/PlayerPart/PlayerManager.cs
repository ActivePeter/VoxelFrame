using Apex.Serialization;
using Swifter.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using VoxelServer.Utils;

namespace VoxelServer.Game.PlayerPart
{
    class PlayerManager
    {
        public static PlayerManager instance;
        int maxId=0;
        bool playerBaseDataChanged = false;
        Dictionary<int, PlayerBaseData> idToPlayerBaseDataDic;
        Dictionary<string, int> nameToIdDic = new Dictionary<string, int>();


        public PlayerManager()
        {
            instance = this;
            loadPlayerData();
            regiPlayer("sss","11233");
            regiPlayer("sss", "11233");
            regiPlayer("ssss", "11233");
            regiPlayer("sssss", "11233");

            savePlayerBaseDataIfNeed();
        }
        private void loadPlayerData()
        {
            //Console.WriteLine(System.IO.Directory.GetCurrentDirectory());
            FileUtils.createIfNotExist("data");
            FileUtils.createIfNotExist("data/playerData");
            string playerBaseDataJson=FileUtils.readFile("data/playerData/baseData.json");
            if (playerBaseDataJson != null)
            {
                idToPlayerBaseDataDic=JsonFormatter.DeserializeObject<Dictionary<int, PlayerBaseData>>(playerBaseDataJson);
                foreach (KeyValuePair<int, PlayerBaseData> item in idToPlayerBaseDataDic)
                {
                    nameToIdDic.Add(item.Value.userName, item.Key);
                }
            }
            else
            {
                idToPlayerBaseDataDic = new Dictionary<int, PlayerBaseData>(); 
            }
        }
        public bool regiPlayer(string username,string pw)
        {
            if (nameToIdDic.ContainsKey(username))
            {
                Console.WriteLine(username + "用户名已经存在，无法注册");
                return false;
            }
            maxId++;
            Player newPlayer = new Player();
            newPlayer.PlayerBaseData.userId= maxId;
            newPlayer.PlayerBaseData.userName = username;
            newPlayer.PlayerBaseData.password = pw;
            nameToIdDic.Add(username, maxId);
            idToPlayerBaseDataDic.Add(newPlayer.PlayerBaseData.userId,newPlayer.PlayerBaseData);

            playerBaseDataChanged = true;
            return true;
        }
        public void savePlayerBaseDataIfNeed()//id:用户名,密码
        {
            if (playerBaseDataChanged)
            {
                playerBaseDataChanged = false;
                string json;
                lock (idToPlayerBaseDataDic)
                {
                    json = JsonFormatter.SerializeObject(idToPlayerBaseDataDic);
                }
                FileUtils.saveFile("data/playerData/baseData.json", json);
                Console.WriteLine(json);
            }
        }
    }
}
