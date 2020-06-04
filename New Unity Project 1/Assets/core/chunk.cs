using System.Collections;
using System.Threading;
using System.Collections.Generic;
using UnityEngine;

public class Chunk
{
    int x;
    int y;
    int z;
    public uniKey[] blockData;
    public byte[] blockRotateData;
    //区块主体
    public GameObject terrain;

    public Chunk(int px, int py, int pz, int sum)
    {
        
        x = px; y = py; z = pz;
        //if (x == -2 && z == -1) Debug.LogError(x + " " + y + " " + z);

        blockData = new uniKey[sum];
        blockRotateData = new byte[sum];
        
    }
}
