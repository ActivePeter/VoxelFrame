using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockShape{
	public Shapes shape;
	public int value;
	//public GameObject ShapeIconObject;
	//public RenderTexture ShapeIcon;
	public BlockShape(Shapes shape1,int value1){
		shape=shape1;
		value=value1;
		
		//IconManager.iconManager.loadShapeIcon(this);
		
        
	}
	//public void loadShapeIcon(GameObject ShapeIconObject,RenderTexture ShapeIcon, Shapes shape1){}
}
