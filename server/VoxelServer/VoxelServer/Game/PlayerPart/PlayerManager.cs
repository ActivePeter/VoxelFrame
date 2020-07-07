using Apex.Serialization;
using Swifter.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Voxel.Network.Pack;
using Voxel.Utils;

namespace VoxelServer.Game.PlayerPart
{
    class PlayerManager
    {
        public static PlayerManager instance;
        int maxId=0;
        bool playerBaseDataChanged = false;
        Dictionary<int, PlayerBaseData> id2PlayerBaseDataDic;
        Dictionary<string, int> name2IdDic = new Dictionary<string, int>();
        Dictionary<int, int> playerId2WorldIdDic=new Dictionary<int, int>();
        public PlayerManager()
        {
            instance = this;
            loadPlayerData();
            regiPlayer("sss","11233");
            regiPlayer("sss", "11233");
            regiPlayer("ssss", "11233");
            regiPlayer("sssss", "11233");

            //savePlayerBaseDataIfNeed();
        }
        private void loadPlayerData()
        {
            //Console.WriteLine(System.IO.Directory.GetCurrentDirectory());
            FileUtils.createIfNotExist("data");
            FileUtils.createIfNotExist("data/playerData");
            string playerBaseDataJson=FileUtils.readFile("data/playerData/baseData.json");
            if (playerBaseDataJson != null)
            {
                id2PlayerBaseDataDic=JsonFormatter.DeserializeObject<Dictionary<int, PlayerBaseData>>(playerBaseDataJson);
                foreach (KeyValuePair<int, PlayerBaseData> item in id2PlayerBaseDataDic)
                {
                    name2IdDic.Add(item.Value.userName, item.Key);
                }
            }
            else
            {
                id2PlayerBaseDataDic = new Dictionary<int, PlayerBaseData>(); 
            }
        }
        public RegiState regiPlayer(string username,string pw)
        {
            if (name2IdDic.ContainsKey(username))
            {
                Console.WriteLine(username + "用户名已经存在，无法注册");
                return RegiState.Exist;
            }
            maxId++;
            Player newPlayer = new Player();
            newPlayer.playerBaseData.userId= maxId;
            newPlayer.playerBaseData.userName = username;
            newPlayer.playerBaseData.password = pw;
            name2IdDic.Add(username, maxId);
            id2PlayerBaseDataDic.Add(newPlayer.playerBaseData.userId,newPlayer.playerBaseData);

            playerBaseDataChanged = true;
            return RegiState.Succ;
        }
        public LoginState loginPlayer(string username, string pw)
        {
            if (name2IdDic.ContainsKey(username))//判断有没有注册
            {
                int id = name2IdDic[username];
                if (playerId2WorldIdDic.ContainsKey(id))
                {
                    return LoginState.InGame;
                }
                else
                {
                    if (id2PlayerBaseDataDic[id].password == pw)
                    {
                        //登入操作

                        return LoginState.Succ;
                    }
                    else
                    {
                        return LoginState.WrongPassOrId;
                    }
                }
            }
            else
            {
                return LoginState.WrongPassOrId;
            }
        }
        public void savePlayerBaseDataIfNeed()//id:用户名,密码
        {
            if (playerBaseDataChanged)
            {
                playerBaseDataChanged = false;
                string json;
                lock (id2PlayerBaseDataDic)
                {
                    json = JsonFormatter.SerializeObject(id2PlayerBaseDataDic);
                }
                FileUtils.saveFile("data/playerData/baseData.json", json);
                Console.WriteLine("data has just been stored");
            }
            else
            {
                Console.WriteLine("data nochange");
            }
        }
    }
}
