using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockShapeAttacher{
	public static BlockShapeAttacher blockShapeAttacher;
	Dictionary<Shapes,BlockShape> shapeDic ;
	// Use this for initialization
	public BlockShapeAttacher(){
		blockShapeAttacher=this;
		shapeDic=new Dictionary<Shapes,BlockShape>();
		InitShapeToDic(Shapes.cube,4);
		InitShapeToDic(Shapes.triPrism,2);
	}
	void InitShapeToDic(Shapes shape,int value){
		shapeDic.Add(shape,new BlockShape(shape,value));
	}
	public BlockShape GetBlockShape(Shapes shape1){
		return shapeDic[shape1];
	}
	public int[] getSwitchCount(int from,int to){
		int lcm=MyTools.lcm(from,to);
		return new int[]{lcm/from,lcm/to};
	}
}
