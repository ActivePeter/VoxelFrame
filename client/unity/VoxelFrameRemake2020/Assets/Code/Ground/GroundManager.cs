using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class GroundManager
{
    ChunkDataLoadThread chunkDataLoadThread;
    private Dictionary<long, Chunk[]> ChunkXzDic;

    private void Init()
    {
        chunkDataLoadThread = ChunkDataLoadThread.getInstance();

    }
    public void updateOldChunks()
    {

    }

}

