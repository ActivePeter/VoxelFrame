using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using VoxelServer.Game.PlayerPart;

namespace VoxelServer.Game.WorldPart
{
    
    class WorldManager
    {
        World world;
        PlayerManager playerManager;


        public WorldManager(PlayerManager playerManager) {
            world = new World();
            this.playerManager = playerManager;
            Thread mainThread = new Thread(gameLoop);
            mainThread.Start();
        }
        private void gameLoop()
        {
            long preMillis= DateTime.Now.Ticks/10000; 
            while (true)
            {
                long curMillis = DateTime.Now.Ticks / 10000;
                long deltaMillis = curMillis - preMillis;
                if (deltaMillis > 50)
                {
                    preMillis = curMillis;
                }
                while (deltaMillis > 50)
                {
                    deltaMillis -= 50;
                    tick();
                }
                Thread.Sleep(1);
            }
        }
        long tickCnt=0;
        private void tick()//进行entity和世界时间的状态更新
        {
            if (tickCnt%900==0)//进行数据存储
            {
                playerManager.savePlayerBaseDataIfNeed();
            }
            world.tick();
            tickCnt++;
        }
    }
}
