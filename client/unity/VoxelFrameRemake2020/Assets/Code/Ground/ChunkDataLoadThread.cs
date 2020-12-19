using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

class ChunkDataLoadThread
{
    private static ChunkDataLoadThread instance;
    bool threadRunning = true;
    public static ChunkDataLoadThread getInstance()
    {
        if (instance == null)
        {
            instance = new ChunkDataLoadThread();
        }
        return instance;
    }
    //xz平面区块列表
    

    public void init()
    {
        ThreadStart threadStart = new ThreadStart(doInThread);
        Thread childThread = new Thread(threadStart);
        childThread.Start();
    }
    public void doInThread()
    {
        while (threadRunning)
        {

        }
    }
}