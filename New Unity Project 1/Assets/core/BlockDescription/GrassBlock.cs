using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrassBlock:BlockDescription{
	
	//static Dictionary<int,GrassBlock> grassBlockDic;
	public BlockShape blockShape;
	public GameObject IconObject;
	public RenderTexture Icon;
    public item ITEM1;
    public byte DirecionsCount;
	static Shapes[] ShapeArr={Shapes.cube,Shapes.triPrism};
	public GrassBlock (Shapes shape){
        switch (shape){
            case Shapes.cube:
                DirecionsCount=6;
                break;
            case Shapes.triPrism:
                DirecionsCount=12;
                break;
        }
		blockShape=BlockShapeAttacher.blockShapeAttacher.GetBlockShape(shape);
		IconManager.iconManager.loadBlockIcon(this);
		if(IconObject==null)Debug.Log("wtf");
	}
	/*public GrassBlock getGrassBlock(Shapes shape){
		if(grassBlockDic==null){
			grassBlockDic= new Dictionary<int,GrassBlock>();
			foreach(Shapes a in ShapeArr){
				grassBlockDic.Add((int)a,new GrassBlock(a));
			}
		}
		return grassBlockDic[(int)shape];
	}*/


    public override Shapes[] GetShapeArr()
    {
		return ShapeArr;
        throw new System.NotImplementedException();
    }

    public override BlockShape GetShape()
    {
		return blockShape;
        throw new System.NotImplementedException();
    }

    public override int GetBlockID()
    {
		return 1;
        throw new System.NotImplementedException();
    }

    public override void DrawSingleBlock(List<int> tri,List<Vector3> ver,List<Vector2> uv)
    {
        switch (blockShape.shape){
            case Shapes.cube:
                cubeBlock cubeBlock1 = new cubeBlock(0, 3, 2, 1, 1, 1, 1);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 0);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 1);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 2);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 3);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 4);
                cubeBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 5);
                break;
            case Shapes.triPrism:
                triPrismBlock triPrismBlock1 = new triPrismBlock(0,3, 2, 1, 1, 1);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 0);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 1);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 2);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 3);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, -Vector3.one/2, 4);
                break;

        } 
		
        //throw new System.NotImplementedException();
    }

    public override RenderTexture GetIcon()
    {
		return this.Icon;
        throw new System.NotImplementedException();
    }

    public override GameObject GetIconObject()
    {
		return this.IconObject;
        throw new System.NotImplementedException();
    }

    public override void SetIconAndObj(GameObject IconObject,RenderTexture Icon)
    {
		this.Icon=Icon;
		this.IconObject=IconObject;
    }

    public override void SetItem(item ITEM)
    {
        this.ITEM1=ITEM;
    }
    public static void LoadAllBlocks(int id,Dictionary<uniKey,BlockDescription> dic){
        dic.Add(MyTools.Unikey(id,(int)Shapes.cube),new GrassBlock(Shapes.cube));
		dic.Add(MyTools.Unikey(id,(int)Shapes.triPrism),new GrassBlock(Shapes.triPrism));
    }

    public override byte GetDirectionsCount()
    {
        return DirecionsCount;
        throw new System.NotImplementedException();
    }

    public override block GetBlockDrawer(byte direction1)
    {
        switch (blockShape.shape){
            case Shapes.cube:
                return new cubeBlock(0,3,2,1,1,1,1);
                break;
            case Shapes.triPrism:
                return new triPrismBlock(0,3, 2, 1, 1, 1);
                break;

        } 
        throw new System.NotImplementedException();
    }
}
