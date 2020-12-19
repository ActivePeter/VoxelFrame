using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemAttacher{
	public Dictionary<uniKey,item> itemDic;
	public static ItemAttacher itemAttacher;
	public ItemAttacher(){
		itemAttacher=this;
		GameObject iconManagerObject =new GameObject("iconManagerObject");
        IconManager iconManager=new IconManager(iconManagerObject);
		BlockShapeAttacher blockShapeAttacher=new BlockShapeAttacher();
		BlockAttacher blockAttacher=new BlockAttacher();
		itemDic = new Dictionary<uniKey, item>();
		foreach(KeyValuePair<uniKey,BlockDescription> kv in blockAttacher.blockDescriptionDic){
			//Debug.Log("asd"+kv.Key[0]+kv.Key[1]);
			itemDic.Add(kv.Key,new item(kv.Value));
		}
	}
	public void getItemInShape(){

	}
}
