using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockObjectCreator {

	public static GameObject CreateBlockObject(BlockDescription block){
		Material diffuseMap;
		List<int> tri = new List<int>();
        List<Vector3> ver = new List<Vector3>();
        List<Vector2> uv = new List<Vector2>();
        GameObject BlockIconObject = new GameObject("ID" + block.GetBlockID()+block.GetShape());
        if (BlockIconObject.GetComponent<MeshFilter>() == null)
        {
            BlockIconObject.AddComponent<MeshFilter>();
        }
        Mesh mesh = BlockIconObject.GetComponent<MeshFilter>().mesh;//添加网格组件，并且添加到本地mesh变量里
        if (BlockIconObject.GetComponent<MeshRenderer>() == null)
        {
            BlockIconObject.AddComponent<MeshRenderer>();
        }

    	diffuseMap = new Material(Shader.Find("Diffuse"));

        BlockIconObject.GetComponent<Renderer>().material = diffuseMap;
        BlockIconObject.GetComponent<Renderer>().material.mainTexture = Resources.Load<Texture>("Texture/atlas");
        block.DrawSingleBlock(tri,ver,uv);
        mesh.vertices = ver.ToArray();
        mesh.uv = uv.ToArray();
        mesh.triangles = tri.ToArray();
        //重置法线
        mesh.RecalculateNormals();
        //重置范围
        mesh.RecalculateBounds();
		return BlockIconObject;
	}
	public static GameObject CreateBlockObjectWithColiAndCenter(BlockDescription block){
		GameObject ColiObject=CreateBlockObject(block);
		ColiObject.AddComponent<MeshCollider>();
        ColiObject.GetComponent<MeshCollider>().convex=true;
		//GameObject objCenter=new GameObject(ColiObject.name+"'s center");
		//ColiObject.transform.SetParent(objCenter.transform);
		//ColiObject.transform.localPosition=new Vector3(-0.5f,-0.5f,-0.5f);

		//return objCenter;
        return ColiObject;
	}
	/*public static GameObject CreateBlockShapeObject(BlockShape blockShape){
		Material diffuseMap;
		List<int> tri = new List<int>();
        List<Vector3> ver = new List<Vector3>();
        List<Vector2> uv = new List<Vector2>();
        GameObject ShapeIconObject = new GameObject("ShapeID:" + blockShape.shape);
        //ShapeIconObjectSet[1]=ShapeIconObject;
        if (ShapeIconObject.GetComponent<MeshFilter>() == null)
        {
            ShapeIconObject.AddComponent<MeshFilter>();
        }
        Mesh mesh = ShapeIconObject.GetComponent<MeshFilter>().mesh;//添加网格组件，并且添加到本地mesh变量里
        if (ShapeIconObject.GetComponent<MeshRenderer>() == null)
        {
            ShapeIconObject.AddComponent<MeshRenderer>();
        }
    	diffuseMap = new Material(Shader.Find("Diffuse"));
        
        ShapeIconObject.GetComponent<Renderer>().material = diffuseMap;
        
        switch (blockShape.shape){
            case Shapes.triPrism:
                triPrismBlock triPrismBlock1 = new triPrismBlock(2);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, Vector3.zero, 0);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, Vector3.zero, 1);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, Vector3.zero, 2);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, Vector3.zero, 3);
                triPrismBlock1.addVerAndTriByParentPosAndSide(ver, tri, uv, Vector3.zero, 4);
                break;
        }
        
        mesh.vertices = ver.ToArray();
        mesh.uv = uv.ToArray();
        mesh.triangles = tri.ToArray();
        //重置法线
        mesh.RecalculateNormals();
        //重置范围
        mesh.RecalculateBounds();
		return ShapeIconObject;
	}*/
}
