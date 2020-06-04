using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockAttacher{
	/*public static int GetShapeCount(int BlockID1){
		return GetBlockDescription(BlockID1).getShapesCount();
	}*/
	public Dictionary<uniKey,BlockDescription> blockDescriptionDic;
	public static BlockAttacher blockAttacher;
	public BlockAttacher(){
		blockAttacher=this;
		blockDescriptionDic=new Dictionary<uniKey,BlockDescription>();
		GrassBlock.LoadAllBlocks(1,blockDescriptionDic);
	}
	public BlockDescription GetBlock(int id1 ,Shapes shape1){
		return blockDescriptionDic[MyTools.Unikey(id1,(int)shape1)];
	}
	public BlockDescription GetBlock(uniKey uk1){
		return blockDescriptionDic[uk1];
	}
	public static uniKey GetEmptyBlock(){
		uniKey empty;
		empty.id1=0;
		empty.id2=0;
		return empty;
	}
}
