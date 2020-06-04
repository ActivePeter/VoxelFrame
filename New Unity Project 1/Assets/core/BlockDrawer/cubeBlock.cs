using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cubeBlock : block
{
    int up, down, left, right, front, behind;
    public cubeBlock(byte direction,int UP,int DOWN,int LEFT,int RIGHT,int FRONT,int BEHIND)
    {
        up = UP;
        down = DOWN;
        left = LEFT;
        right = RIGHT;
        front = FRONT;
        behind = BEHIND;
        
    }
    float[] VerArr=new float[]{//相对坐标
        //up
        0,1,0,//v1
        1,1,0,
        0,1,1,
        1,1,1,
        //down
        0,0,0,
        0,0,1,
        1,0,0,
        1,0,1,
        //right
        1,0,0,
        1,0,1,
        1,1,0,
        1,1,1,
        //left
        0,0,1,
        0,0,0,
        0,1,1,
        0,1,0,
        //forward
        1,0,1,
        0,0,1,
        1,1,1,
        0,1,1,
        //back
        0,0,0,
        1,0,0,
        0,1,0,
        1,1,0

    };
    public override bool ifEmptySelf(Vector3 side)
    {
        return false;
        
    }
    public override bool ifEmptyOther(int cx, int cy, int cz, int x, int y, int z, TerrainManager tm,Vector3 side)
    {

        
        if (!tm.ifEnableAfterCalculatePos(x, y, z, cx, cy, cz))
        {
            return false;
        }
        else if (tm.getBlockType(x, y, z, cx, cy, cz).Equals(MyTools.Unikey(0,0)))
        {
            return true;

        } else if (BlockAttacher.blockAttacher.GetBlock(tm.getBlockType(x, y, z, cx, cy, cz)).GetBlockDrawer(tm.getRotate(x, y, z, cx, cy, cz)).ifEmptySelf(side)){//tm.getBlockLoader(tm.getBlockType(x, y, z, cx, cy, cz),tm.getRotate(x, y, z, cx, cy, cz)).ifEmptySelf(side)) {
            
            return true;
        }
        else
        {
            
            return false;
        }
    }
    public void addVerAndTriByParentPosAndSide(List<Vector3> ver, List<int> tri, List<Vector2> uv,Vector3 ParentPos,byte side){
        Vector2[] a;
        switch (side){
            case 0://up
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));
                a = MyTools.calcuUV(up);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);
                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                break;
            case 1://down
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));

                a = MyTools.calcuUV(down);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 4);
                break;
            case 2://right
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));

                a = MyTools.calcuUV(right);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 4);
                break;
            case 3://left
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));

                a = MyTools.calcuUV(left);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                break;
            case 4://forward
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));

                a = a = MyTools.calcuUV(front);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);

                tri.Add(ver.Count - 4);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                break;
            case 5://forward
                ver.Add(new Vector3(ParentPos.x+VerArr[0+side*12], ParentPos.y+VerArr[1+side*12], ParentPos.z+VerArr[2+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[3+side*12], ParentPos.y+VerArr[4+side*12], ParentPos.z+VerArr[5+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[6+side*12], ParentPos.y+VerArr[7+side*12], ParentPos.z+VerArr[8+side*12]));
                ver.Add(new Vector3(ParentPos.x+VerArr[9+side*12], ParentPos.y+VerArr[10+side*12], ParentPos.z+VerArr[11+side*12]));
                a = MyTools.calcuUV(behind);
                uv.Add(a[0]);
                uv.Add(a[1]);
                uv.Add(a[2]);
                uv.Add(a[3]);

                tri.Add(ver.Count - 4);

                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 3);
                tri.Add(ver.Count - 2);
                tri.Add(ver.Count - 1);
                tri.Add(ver.Count - 4);
                break;

        }
    }
    public override void addVerAndTri(List<Vector3> ver, List<int> tri, List<Vector2> uv, int cx, int cy, int cz, int x, int y, int z, TerrainManager tm)
    {
        Vector3 WorldPo=new Vector3(tm.GetWorldPo(cx, x),tm.GetWorldPo(cy, y),tm.GetWorldPo(cz, z));        //up block
        if(ifEmptyOther(cx,cy,cz,x,y+1,z,tm,Vector3.down))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,0);
        }
        //down
        if (ifEmptyOther(cx, cy, cz, x, y-1, z, tm, Vector3.up))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,1);
        }
        //
        if (ifEmptyOther(cx, cy, cz, x+1, y, z, tm, Vector3.left))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,2);
        }
        if (ifEmptyOther(cx, cy, cz, x-1, y, z, tm, Vector3.right))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,3);
        }
        if (ifEmptyOther(cx, cy, cz, x, y, z+1, tm, Vector3.back))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,4);
        }
        if (ifEmptyOther(cx, cy, cz, x, y, z-1, tm, Vector3.forward))
        {
            addVerAndTriByParentPosAndSide(ver,tri,uv,WorldPo,5);
        }
    }

    public override void getBlockObjectRotate(GameObject BlockObject)
    {
        //throw new NotImplementedException();
    }
}
