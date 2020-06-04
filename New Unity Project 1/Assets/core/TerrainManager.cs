using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Assets.core.Base;

public class TerrainManager : MonoBehaviour
{
    public static TerrainManager terrainManager;
    
    //材质
    
    //地图加载半径
    public int r;
    //当前人所在区块坐标
    public int CurCx, CurCy, CurCz;
    //当前人所在坐标
    public float cpx, cpy, cpz;
    //即将销毁区块列表
    public List<GameObject> terrainWaitToClean;
    
    
    //xz平面区块列表
    public Dictionary<long, Chunk[]> ChunkXZ_Dic;
    
    private bool isDrawing = false;//防止其他含update脚本引用时冲突

    //生成信息
    public int chunkSize;//长宽高
    private int groundHeight;//地面高度
   


    //1
    void Start()
    {
        terrainManager=this;
        
        Init(16, 4);//初始化数据
        Generate();
        //SetTerrain(10, 10, 10, 5);
    }
    void Update()
    {
    }


    //2
    private void Init(int cs, int groundH)
    {
        r = 8;
        ChunkXZ_Dic = new Dictionary<long, Chunk[]>();
        chunkSize = cs;//初始化区块尺寸并赋值
        groundHeight = groundH;//给地面高度赋值

    }

    // 通过参数生成地形3
    private void Generate()
    {
        StartCoroutine(loading());
        //InitChunk(0, 0);
        //InitChunk(1, 0);
        //InitChunk(0, 1);
        //InitChunk(1, 1);
    }
    private int[] getClosestChunk(int cx, int cy, int cz)
    {
        int OldDis = r * r *3+ 1;
        int[] closest = new int[3];//最近区块左边xyz
        for (int z = cz - r; z <= cz + r; z++)
        {
            for (int x = cx - r; x <= cx + r; x++)
            {
                //for (int y = cy - 2; x <= cy + 2; y++)
                //{
                int y = cy - 2;
                int dis = (x - cx) * (x - cx) + (z - cz) * (z - cz);
                if (dis > r * r) continue;
                if (ifDrawn(x, y, z)) continue;
                if (OldDis > dis)
                {
                    OldDis = dis;
                    closest[0] = x;
                    closest[1] = y;
                    closest[2] = z;
                }

                // }
            }
        }
        return closest;
    }
    private IEnumerator loading()
    {


        while (true)
        {
            yield return new WaitForSeconds(0.01f);
            int[] a = getClosestChunk(CurCx, 3, CurCz);
            if (a[1] != 0)
            {
                yield return FirstLoadChunkDataOnly(a[0], a[1], a[2]);
                reDrawChunk(a[0], a[1], a[2]);
            }
        }
    }
    //4

    private bool ifInRange(int x, int z)
    {
        int i = (CurCx - x);
        int j = CurCz - z;
        if (i * i + j * j > r * r)
        {
            return false;
        }
        else
        {
            return true;
        }

    }
    private IEnumerator checkToClean(GameObject terrain, int x, int z)
    {
        while (terrain != null)
        {
            yield return new WaitForSeconds(3);
            if (!ifInRange(x, z))
            {
                Destroy(terrain);
            }
        }
    }

    //5重绘区块。比如放置方块后
    private void reDrawChunk(int cx, int cy, int cz)
    {
        Chunk chunk = ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy];
        if (chunk.terrain == null)
        {
            chunk.terrain = new GameObject();//初始化区间;
            chunk.terrain.transform.parent = this.transform;//并入map名下
            chunk.terrain.name = "Pos_" + cx + "," + cy + "," + cz;//设置Chunk名字
            chunk.terrain.layer = 8;
            StartCoroutine(checkToClean(chunk.terrain, cx, cz));
        }
        MeshMaker meshMaker = new MeshMaker();
        Loom.RunAsync(
            () =>
            {
                meshMaker.setVertives(cx, cy, cz, ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData, ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData);
                Loom.QueueOnMainThread(() =>
                {
                    meshMaker.drawMesh(chunk.terrain);
                });
            }
        );
        
    }
    private bool ifHasPerson(int px, int py, int pz)
    {
        if(px==Mathf.FloorToInt(cpx)&& pz== Mathf.FloorToInt(cpz))
        {
            
            if(py== Mathf.FloorToInt(cpy-0.1f)|| py == Mathf.FloorToInt(cpy +1.2f) || py == Mathf.FloorToInt(cpy + 0.8f))
            {return true;

            }else
            {
                return false;
            }
            
        }else
        {
            return false;
        }
    }
    //用于自动恢复方块 若所在坐标有方块就选区附近区域放置方块
    public void BuildBlockInEmpty(int px, int py, int pz, uniKey blockID, byte direction)
    {
        uniKey oldBlock;
        while (isDrawing) { }//等待上一次绘制完成，防止冲突
        isDrawing = true;
        
        int opx=px;
        int opy=py;
        int opz=pz;

        int cx = Mathf.FloorToInt(px) >> 4;
        int cy = Mathf.FloorToInt(py) >> 4;
        int cz = Mathf.FloorToInt(pz) >> 4;

        px = px - chunkSize * cx;
        py = py - chunkSize * cy;
        pz = pz - chunkSize * cz;

        if (cy >= 0)
        {
            if (ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF) && ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF & 0xFFFFFFFF][cy] != null)
            {
                oldBlock = ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)];
                if (oldBlock.Equals(BlockAttacher.GetEmptyBlock()))
                {
                    Debug.Log("零");
                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)] = blockID;
                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData[getBlockIndex(px, py, pz)] = direction;
                    reDrawChunk(cx, cy, cz);
                    if (px == 0)
                    {
                        reDrawChunk(cx - 1, cy, cz);
                    }
                    else if (py == 0)
                    {
                        if (cy > 0)
                        {
                            reDrawChunk(cx, cy - 1, cz);

                        }
                    }
                    else if (pz == 0)
                    {
                        reDrawChunk(cx, cy, cz - 1);
                    }
                    else if (px == 15)
                    {
                        reDrawChunk(cx + 1, cy, cz);
                    }
                    else if (py == 15)
                    {
                        reDrawChunk(cx, cy + 1, cz);
                    }
                    else if (pz == 15)
                    {
                        reDrawChunk(cx, cy, cz + 1);
                    }
                }else{
                    int[] emptyAround = lookForEmptyAround(opx, opy, opz);
                    Debug.Log(emptyAround[0]+" "+emptyAround[1]+" "+emptyAround[2]+" sss");
                    cx = Mathf.FloorToInt(emptyAround[0]) >> 4;
                    cy = Mathf.FloorToInt(emptyAround[1]) >> 4;
                    cz = Mathf.FloorToInt(emptyAround[2]) >> 4;

                    px = emptyAround[0] - chunkSize * cx;
                    py = emptyAround[1] - chunkSize * cy;
                    pz = emptyAround[2] - chunkSize * cz;

                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)] = blockID;
                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData[getBlockIndex(px, py, pz)] = direction;
                    reDrawChunk(cx, cy, cz);
                    if (px == 0)
                    {
                        reDrawChunk(cx - 1, cy, cz);
                    }
                    else if (py == 0)
                    {
                        if (cy > 0)
                        {
                            reDrawChunk(cx, cy - 1, cz);

                        }
                    }
                    else if (pz == 0)
                    {
                        reDrawChunk(cx, cy, cz - 1);
                    }
                    else if (px == 15)
                    {
                        reDrawChunk(cx + 1, cy, cz);
                    }
                    else if (py == 15)
                    {
                        reDrawChunk(cx, cy + 1, cz);
                    }
                    else if (pz == 15)
                    {
                        reDrawChunk(cx, cy, cz + 1);
                    }
                }

            }

        }
        isDrawing = false;
    }
    private int[] lookForEmptyAround(int px, int py, int pz)
    {
        int halfWidth = 10;
        int oldDis=halfWidth*halfWidth+2;
        int[] closestEmpty= new int[3];
        
        int pxToWorld =px;
        int pyToWorld =py;
        int pzToWorld =pz;
        //Debug.Log("aaa" + px + "ob" + py + "ob" + pz);
        for (int z = pzToWorld - 1; z <= pzToWorld + 1; z++)
        {
            for (int x = pxToWorld - 1; x <= pxToWorld + 1; x++)
            {
                for (int y = pyToWorld - halfWidth; y <= pyToWorld + halfWidth*10; y++)
                {
                    int cy = Mathf.FloorToInt(y) >> 4;
                    if (cy >= 0)
                    {
                        int cx = Mathf.FloorToInt(x) >> 4;
                        int cz = Mathf.FloorToInt(z) >> 4;

                        if (ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF) && ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF & 0xFFFFFFFF][cy] != null)
                        {
                            

                            px = x - chunkSize * cx;
                            py = y - chunkSize * cy;
                            pz = z - chunkSize * cz;

                            uniKey oldBlock = ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)];
                            //
                            if (oldBlock.Equals(BlockAttacher.GetEmptyBlock()))
                            {
                                int dis = (x - pxToWorld) * (x - pxToWorld) + (z - pzToWorld) * (z - pzToWorld)+(y - pyToWorld)*(y - pyToWorld);
                                
                                if (oldDis > dis)
                                {
                                    oldDis = dis;
                                    
                                    closestEmpty[0] = x;
                                    closestEmpty[1] = y;
                                    closestEmpty[2] = z;
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
        return closestEmpty;
    }
    public byte GetBlockRotation(int px, int py, int pz){
        int cx = Mathf.FloorToInt(px) >> 4;
        int cy = Mathf.FloorToInt(py) >> 4;
        int cz = Mathf.FloorToInt(pz) >> 4;
        px = px - chunkSize * cx;
        py = py - chunkSize * cy;
        pz = pz - chunkSize * cz;

        if (cy >= 0 || ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF) && ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF & 0xFFFFFFFF][cy] != null)
        {
            return ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData[getBlockIndex(px, py, pz)];
        }
        return 80;

         
    }
    //改变方块数据并且重新加载相关区块
    public uniKey BuildBlock(int px, int py, int pz, uniKey blockID, byte direction)
    {
        uniKey oldBlock =BlockAttacher.GetEmptyBlock();
        while (isDrawing) { }//等待上一次绘制完成，防止冲突
        isDrawing = true;

        int cx = Mathf.FloorToInt(px) >> 4;
        int cy = Mathf.FloorToInt(py) >> 4;
        int cz = Mathf.FloorToInt(pz) >> 4;
        px = px - chunkSize * cx;
        py = py - chunkSize * cy;
        pz = pz - chunkSize * cz;

        if (cy >= 0)
        {
            if (ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF) && ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF & 0xFFFFFFFF][cy] != null)
            {
                oldBlock = ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)];
                uniKey empty=BlockAttacher.GetEmptyBlock();
                if (!blockID.Equals(empty)&&oldBlock.Equals(empty)||blockID.Equals(empty)&&!oldBlock.Equals(empty))
                {
                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(px, py, pz)] = blockID;
                    ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData[getBlockIndex(px, py, pz)] = direction;
                    reDrawChunk(cx, cy, cz);
                    if (px == 0)
                    {
                        reDrawChunk(cx - 1, cy, cz);
                    }
                    else if (py == 0)
                    {
                        if (cy > 0)
                        {
                            reDrawChunk(cx, cy - 1, cz);

                        }
                    }
                    else if (pz == 0)
                    {
                        reDrawChunk(cx, cy, cz - 1);
                    }
                    else if (px == 15)
                    {
                        reDrawChunk(cx + 1, cy, cz);
                    }
                    else if (py == 15)
                    {
                        reDrawChunk(cx, cy + 1, cz);
                    }
                    else if (pz == 15)
                    {
                        reDrawChunk(cx, cy, cz + 1);
                    }
                }

            }

        }
        isDrawing = false;
        return oldBlock;
    }
    
    /// 绘制网格
    
    
    //根据区块和方块坐标获得世界坐标（x或y或z
    public float GetWorldPo(int cxyz, float localxyz)
    {
        return cxyz * chunkSize + localxyz;
    }
    /// 遍历区块生成顶点信息
    

    //这个包含方块序号和坐标的对应规则，可以直接通过方块坐标获得方块序号
    public int getBlockIndex(int x, int y, int z)
    {
        return (z + y * (chunkSize) + (x * (chunkSize) * (chunkSize)));
    }
    //根据坐标获取方块种类，并讨论边缘情况
    public uniKey getBlockType(int x, int y, int z, int cx, int cy, int cz)
    {
        if (x < 0)
        {
            x = x + chunkSize;
            cx = cx - 1;
        }
        else if (x >= chunkSize)
        {
            x = x - chunkSize;
            cx = cx + 1;
        }

        if (y < 0)
        {
            y = y + chunkSize;
            cy = cy - 1;
        }
        else if (y >= chunkSize)
        {
            y = y - chunkSize;
            cy = cy + 1;
        }

        if (z < 0)
        {
            z = z + chunkSize;
            cz = cz - 1;
        }
        else if (z >= chunkSize)
        {
            z = z - chunkSize;
            cz = cz + 1;
        }
        FirstLoadChunkDataOnly(cx, cy, cz);
        return ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[(z + y * (chunkSize) + (x * (chunkSize) * (chunkSize)))];


    }
    public byte getRotate(int x, int y, int z, int cx, int cy, int cz)
    {
        if (x < 0)
        {
            x = x + chunkSize;
            cx = cx - 1;
        }
        else if (x >= chunkSize)
        {
            x = x - chunkSize;
            cx = cx + 1;
        }

        if (y < 0)
        {
            y = y + chunkSize;
            cy = cy - 1;
        }
        else if (y >= chunkSize)
        {
            y = y - chunkSize;
            cy = cy + 1;
        }

        if (z < 0)
        {
            z = z + chunkSize;
            cz = cz - 1;
        }
        else if (z >= chunkSize)
        {
            z = z - chunkSize;
            cz = cz + 1;
        }
        FirstLoadChunkDataOnly(cx, cy, cz);

        return ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockRotateData[getBlockIndex(x, y, z)];


    }
    //获取方块方向
    public bool ifEnableAfterCalculatePos(int x, int y, int z, int cx, int cy, int cz)
    {
        if (x < 0)
        {
            x = x + chunkSize;
            cx = cx - 1;
        }
        else if (x >= chunkSize)
        {
            x = x - chunkSize;
            cx = cx + 1;
        }

        if (y < 0)
        {
            y = y + chunkSize;
            cy = cy - 1;
        }
        else if (y >= chunkSize)
        {
            y = y - chunkSize;
            cy = cy + 1;
        }

        if (z < 0)
        {
            z = z + chunkSize;
            cz = cz - 1;
        }
        else if (z >= chunkSize)
        {
            z = z - chunkSize;
            cz = cz + 1;
        }
        if (cy < 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    private bool ifDrawn(int cx, int cy, int cz)
    {
        if (!(ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF)))
        {
            return false;
        }
        else if (ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].terrain == null)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    //初次加载区块操作，仅信息
    public bool FirstLoadChunkDataOnly(int cx, int cy, int cz)
    {
        //if (cy ==0) { Debug.Log(0000); }   
        if (cy < 0)
        {
            Debug.LogError("Out Of Range");
            return true;
        }
        else
        {
            if (!(ChunkXZ_Dic.ContainsKey((long)cx << 32 | cz & 0xFFFFFFFF)))
            {
                Chunk Chunk = new Chunk(cx, cy, cz, (int)(chunkSize * chunkSize * chunkSize));


                for (int bx = 0; bx < chunkSize; bx++)
                {
                    for (int by = 0; by < chunkSize; by++)
                    {
                        for (int bz = 0; bz < chunkSize; bz++)
                        {
                            if (by + cy * chunkSize - chunkSize <= groundHeight)
                            {
                                Chunk.blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(1,0);
                            }
                            else
                            {
                                Chunk.blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(0,0);
                            }


                        }

                    }

                }
                Chunk[] Chunky = new Chunk[11]; Chunky[cy] = Chunk;
                ChunkXZ_Dic.Add(((long)cx << 32 | cz & 0xFFFFFFFF), Chunky);

            }
            else if (ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy] == null)
            {
                Chunk Chunk = new Chunk(cx, cy, cz, (chunkSize * chunkSize * chunkSize));

                for (int bx = 0; bx < chunkSize; bx++)
                {
                    for (int by = 0; by < chunkSize; by++)
                    {
                        for (int bz = 0; bz < chunkSize; bz++)
                        {
                            if (by + cy * chunkSize - chunkSize <= groundHeight)
                            {
                                Chunk.blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(1,0);
                            }
                            else
                            {
                                Chunk.blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(0,0);
                            }


                        }

                    }

                }
                ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy] = Chunk;
            }
            else if (ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData == null)
            {
                for (int bx = 0; bx < chunkSize; bx++)
                {
                    for (int by = 0; by < chunkSize; by++)
                    {
                        for (int bz = 0; bz < chunkSize; bz++)
                        {
                            if (by + cy * chunkSize - chunkSize <= groundHeight)
                            {
                                ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(1,0);
                            }
                            else
                            {
                                ChunkXZ_Dic[(long)cx << 32 | cz & 0xFFFFFFFF][cy].blockData[getBlockIndex(bx, by, bz)] = MyTools.Unikey(0,0);
                            }


                        }

                    }

                }
            }
            return false;

        }


    }
    /// <summary>
    /// 生成UV信息
    /// </summary>
    /// <returns></returns>
    /*private Vector2[] GetUV()
    {
        int sum = Mathf.FloorToInt((segment.x + 1) * (segment.y + 1));
        uvs = new Vector2[sum];
        float u = 1.0F / segment.x;
        float v = 1.0F / segment.y;
        uint index = 0;
        for (int i = 0; i < segment.y + 1; i++)
        {
            for (int j = 0; j < segment.x + 1; j++)
            {
                uvs[index] = new Vector2(j * u, i * v);
                index++;
            }
        }

        return uvs;
    }*/

}
