using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IconManager {
    public static IconManager iconManager;
	GameObject iconManagerObject;
	
    int itemIconCount=0;
    
    int ShapeIconCount=0;
	public IconManager(GameObject iconManagerObject1){
		iconManagerObject=iconManagerObject1;
        iconManager=this;
    }
	public void loadBlockIcon(BlockDescription block){
        GameObject BlockIconObject= BlockObjectCreator.CreateBlockObject(block);
        //重置范围
        
        BlockIconObject.transform.SetParent(iconManagerObject.transform);
        BlockIconObject.transform.position = GetPosition(itemIconCount + ShapeIconCount + 1);
        GameObject cam1 = CreateCamera("camera of " + block.GetBlockID()+block.GetShape());
        RenderTexture BlockIcon = new RenderTexture(200, 200, 0);
        Camera camComp = cam1.GetComponent<Camera>();
        camComp.targetTexture = BlockIcon;
        cam1.transform.SetParent(BlockIconObject.transform);
        cam1.transform.localPosition = new Vector3(-0.59f, 1.09f, -0.89f);
        cam1.transform.Rotate(0, 33.9f, 0);
        cam1.transform.Rotate(45, 0, 0);
        camComp.orthographic = true;
        camComp.clearFlags = CameraClearFlags.SolidColor;
        camComp.orthographicSize = 0.94f;
        camComp.renderingPath = RenderingPath.VertexLit;

        block.SetIconAndObj(BlockIconObject,BlockIcon);
        itemIconCount++;
    }
    /*public void loadShapeIcon(BlockShape blockShape){
        GameObject ShapeIconObject=BlockObjectCreator.CreateBlockShapeObject(blockShape);
        
        ShapeIconObject.transform.SetParent(iconManagerObject.transform);
        ShapeIconObject.transform.position = GetPosition(itemIconCount + ShapeIconCount + 1);
        GameObject cam1 = CreateCamera("camera of " + blockShape.shape);
        RenderTexture ShapeIcon = new RenderTexture(200, 200, 0);
        //ShapeIconSet[1] = icon;
        Camera camComp = cam1.GetComponent<Camera>();
        camComp.targetTexture = ShapeIcon;
        cam1.transform.SetParent(ShapeIconObject.transform);
        //Debug.LogError(ShapeIconObject.transform.position);
        cam1.transform.localPosition = new Vector3(-0.26f, 1.88f, -0.61f);
        //Debug.LogError(new Vector3(-0.26f,1.88f,-0.61f)+ShapeIconObject.transform.position);

        cam1.transform.Rotate(0, 33.9f, 0);
        cam1.transform.Rotate(45, 0, 0);

        camComp.orthographic = true;
        camComp.clearFlags = CameraClearFlags.SolidColor;
        camComp.orthographicSize = 0.94f;
        camComp.renderingPath = RenderingPath.VertexLit;

        blockShape.ShapeIcon=ShapeIcon;
        blockShape.ShapeIconObject=ShapeIconObject;
        //addToShapeArr(ID1, ShapeIconObject, icon);
        ShapeIconCount++;
    }*/
   
    Vector3 GetPosition(int Count){
        int x=Count/64;
        int z=(Count-x*64);
        return -(new Vector3(x,0,z)+Vector3.one)*3;
    }
    
	GameObject CreateCamera(string name1){
		GameObject cam=new GameObject(name1);
		cam.AddComponent<Camera>();
		return cam;
	}
}
