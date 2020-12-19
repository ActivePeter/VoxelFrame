using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class block{

    public abstract void addVerAndTri(List<Vector3> ver, List<int> tri,List<Vector2> uv, int cx, int cy, int cz, int x, int y, int z, TerrainManager tm);
    public abstract bool ifEmptyOther(int cx, int cy, int cz, int x, int y, int z, TerrainManager tm, Vector3 side);

    public abstract bool ifEmptySelf(Vector3 side);
    public abstract void getBlockObjectRotate(GameObject BlockObject);

}
