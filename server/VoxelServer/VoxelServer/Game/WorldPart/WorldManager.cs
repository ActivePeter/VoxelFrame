using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace VoxelServer.Game.WorldPart
{
    
    class WorldManager
    {
        World world;
        public WorldManager() {
            world = new World();
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
                preMillis = curMillis;
                while (deltaMillis > 50)
                {
                    deltaMillis -= 50;
                    tick();
                }
                Thread.Sleep(1);
            }
        }
        private void tick()//进行entity和世界时间的状态更新
        {

        }
    }
}
