using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BlockDescription{
	public abstract byte GetDirectionsCount();
	public abstract Shapes[] GetShapeArr();
	public abstract BlockShape GetShape();
	public abstract int GetBlockID();

	public abstract void DrawSingleBlock(List<int> tri,List<Vector3> ver,List<Vector2> uv);
	public abstract RenderTexture GetIcon();

	public abstract GameObject GetIconObject();

	public abstract void SetIconAndObj(GameObject IconObject,RenderTexture Icon);
	public abstract void SetItem(item ITEM);
	public abstract block GetBlockDrawer(byte direction1);
}
