using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class triPrismBlock : block
{
    int UP,DOWN,RIGHT,BACK,SLOPE;
    byte turns;
    byte dir;
    public override bool ifEmptySelf(Vector3 side)
    {
        
        if(Vector3.Dot( getVectorRoatated(new Vector3(0.5f, 0, -0.5f)),side)<-0.0000001|| Vector3.Dot(getVectorRoatated(new Vector3(0, -0.5f, 0)), side) < -0.0000001|| Vector3.Dot(getVectorRoatated(new Vector3(0, 0.5f, 0)), side) < -0.0000001) {
            
            return true;
        }else
        {
            return false;
        }
        

    }
    public override bool ifEmptyOther(int cx, int cy, int cz, int x, int y, int z, TerrainManager tm, Vector3 side)
    {
        if (tm.FirstLoadChunkDataOnly(cx, cy, cz))
        {
            return false;
        }
        else if (tm.getBlockType(x, y, z, cx, cy, cz).Equals(MyTools.Unikey(0,0)))
        {
            
            return true;

        }
        else if (BlockAttacher.blockAttacher.GetBlock(tm.getBlockType(x, y, z, cx, cy, cz)).GetBlockDrawer(tm.getRotate(x, y, z, cx, cy, cz)).ifEmptySelf(side))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   
    public triPrismBlock(byte direction,int up,int down,int right,int back,int slope)
    {
        
        UP=up;
        DOWN=down;
        RIGHT=right;
        BACK=back;
        SLOPE=slope;

        if (direction / 4 > 0)
        {
            if (direction / 8 > 0)
            {
                dir = 2;
                turns = (byte)(direction - 4);
                
            }
            else
            {
                turns = (byte)(direction - 4);
                dir = 1;
            }
        }
        else
        {
            turns = direction;
            dir = 0;
        }


    }
    private Vector3 getVectorRoatated(Vector3 v)
    {
        
        if (dir==0)
        {
            v = Quaternion.AngleAxis(90*turns, Vector3.up) * v;
        }else if(dir == 1)
        {
            v = Quaternion.AngleAxis(90, Vector3.left) * v;
            v = Quaternion.AngleAxis(90*turns, Vector3.up) * v;
        }
        else
        {
            v = Quaternion.AngleAxis(-90, Vector3.left) * v;
            v = Quaternion.AngleAxis(90 * turns, Vector3.up) * v;
        }
        
        return v;
    }
    private Vector3 fixVec(Vector3 vec)
    {
        vec.x = Mathf.RoundToInt(vec.x);
        vec.y = Mathf.RoundToInt(vec.y);
        vec.z = Mathf.RoundToInt(vec.z);
        return vec;
    }
    private int FTI(float a)
    {
        return Mathf.RoundToInt(a);
    }
    public void addVerAndTriByParentPosAndSide(List<Vector3> ver, List<int> tri, List<Vector2> uv, Vector3 ParentPos, byte side)
    {
        Vector3 middle = ParentPos + new Vector3(0.50f, 0.50f, 0.50f);
        Vector3 v1 = middle + getVectorRoatated(new Vector3(-0.50f, 0.50f, -0.50f));
        Vector3 v2 = middle + getVectorRoatated(new Vector3(0.50f, 0.50f, -0.50f));
        Vector3 v3 = middle + getVectorRoatated(new Vector3(0.50f, 0.50f, 0.50f));
        Vector3 v4 = middle + getVectorRoatated(new Vector3(-0.50f, -0.50f, -0.50f));
        Vector3 v5 = middle + getVectorRoatated(new Vector3(0.50f, -0.50f, -0.50f));
        Vector3 v6 = middle + getVectorRoatated(new Vector3(0.50f, -0.50f, 0.50f));

        Vector2[] uvarr;

        switch (side)
        {
            case 0://up
                ver.Add(v1);
                ver.Add(v2);
                ver.Add(v3);

                uvarr = MyTools.calcuUV(UP);
                uv.Add(uvarr[0]);
                uv.Add(uvarr[1]);
                uv.Add(uvarr[3]);

                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 3);
                break;
            case 1://DOWN
                ver.Add(v4);
                ver.Add(v6);
                ver.Add(v5);

                uvarr = MyTools.calcuUV(DOWN);
                uv.Add(uvarr[2]);
                uv.Add(uvarr[1]);
                uv.Add(uvarr[3]);

                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 3);
                break;
            case 2://RIGHT
                ver.Add(v2);
                ver.Add(v3);
                ver.Add(v6);
                ver.Add(v5);

                uvarr = MyTools.calcuUV(RIGHT);
                uv.Add(uvarr[2]);
                uv.Add(uvarr[3]);
                uv.Add(uvarr[1]);
                uv.Add(uvarr[0]);

                tri.Add(ver.Count - 1);

                tri.Add(ver.Count - 3); tri.Add(ver.Count - 2);

                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 3);
                break;
            case 3://BACK
                ver.Add(v1);
                ver.Add(v2);
                ver.Add(v4);
                ver.Add(v5);

                uvarr = MyTools.calcuUV(BACK);
                uv.Add(uvarr[2]);
                uv.Add(uvarr[3]);
                uv.Add(uvarr[0]);
                uv.Add(uvarr[1]);

                tri.Add(ver.Count - 4);

                tri.Add(ver.Count - 3); tri.Add(ver.Count - 2);

                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 3);
                break;
            case 4://SLOPE
                ver.Add(v1);
                ver.Add(v3);
                ver.Add(v4);
                ver.Add(v6);

                uvarr = MyTools.calcuUV(BACK);
                uv.Add(uvarr[3]);
                uv.Add(uvarr[2]);
                uv.Add(uvarr[1]);
                uv.Add(uvarr[0]);

                tri.Add(ver.Count - 3);

                tri.Add(ver.Count - 4); tri.Add(ver.Count - 1);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                break;
        }
    }
    //if (tm.getBlockType(x + (int)vu.x, y + (int)vu.y, z + (int)vu.z, cx, cy, cz) == 0 || Vector3.Dot(tm.getDirection(x + (int)vu.x, y + (int)vu.y, z + (int)vu.z, cx, cy, cz), vu) > 0)
    //{

    //DrawTriU(1, ver, tri, cx, cy, cz, x, y, z, tm);
    //}
    //Debug.Log(Mathf.RoundToInt()vr.z);



    public override void addVerAndTri(List<Vector3> ver, List<int> tri, List<Vector2> uv, int cx, int cy, int cz, int x, int y, int z, TerrainManager tm)
    {
        //Vector3 middle = new Vector3(tm.GetWorldPo(cx, x), tm.GetWorldPo(cy, y), tm.GetWorldPo(cz, z)) + new Vector3(0.50f, 0.50f, 0.50f);
        

        Vector3 vu = getVectorRoatated(Vector3.up);
        Vector3 vd = getVectorRoatated(Vector3.down);
        Vector3 vb = getVectorRoatated(Vector3.back);
        Vector3 vr = getVectorRoatated(Vector3.right);

        fixVec(vu);
        fixVec(vd);
        fixVec(vb);
        fixVec(vr);
        Vector3 WorldPo=new Vector3(tm.GetWorldPo(cx, x), tm.GetWorldPo(cy, y), tm.GetWorldPo(cz, z));
        //up block
        if(ifEmptyOther( cx, cy, cz, x + FTI(vu.x), y + FTI(vu.y), z + FTI(vu.z),tm, -vu))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,0);

        }
        if (ifEmptyOther( cx, cy, cz,x + FTI(vd.x), y +FTI(vd.y), z + FTI(vd.z), tm, -vd))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,1);

        }
        if (ifEmptyOther( cx, cy, cz,x + FTI(vr.x), y + FTI(vr.y), z + FTI(vr.z), tm,- vr))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,2);

        }
        if (ifEmptyOther( cx, cy, cz,x + FTI(vb.x), y + FTI(vb.y), z + FTI(vb.z), tm,- vb))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,3);

        }
        //if (tm.getBlockType(x + (int)vu.x, y + (int)vu.y, z + (int)vu.z, cx, cy, cz) == 0 || Vector3.Dot(tm.getDirection(x + (int)vu.x, y + (int)vu.y, z + (int)vu.z, cx, cy, cz), vu) > 0)
        //{

        //DrawTriU(1, ver, tri, cx, cy, cz, x, y, z, tm);
        //}
        //Debug.Log(Mathf.RoundToInt()vr.z);
        addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,4);
    }

    public override void getBlockObjectRotate(GameObject BlockObject){
        if (dir==0)
        {
            BlockObject.transform.localEulerAngles=new Vector3(0,turns*90,0);
            //v = Quaternion.AngleAxis(90*turns, Vector3.up) * v;
        }else if(dir == 1)
        {
            BlockObject.transform.localEulerAngles=new Vector3(0,turns*90-90,-90);
            //v = Quaternion.AngleAxis(90, Vector3.left) * v;
            //v = Quaternion.AngleAxis(90*turns, Vector3.up) * v;
        }
        else
        {
            BlockObject.transform.localEulerAngles=new Vector3(0,turns*90-90,90);
            //v = Quaternion.AngleAxis(-90, Vector3.left) * v;
            //v = Quaternion.AngleAxis(90 * turns, Vector3.up) * v;
        }
        
            
        
    }
    
}
