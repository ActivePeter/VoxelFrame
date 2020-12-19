using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.core.Base
{
    class MeshMaker
    {
        static private Material diffuseMap;
        static private TerrainManager terrainManager;
        static private Texture publicTexture;

        //顶点、uv、三角形
        private Vector3[] vertives;
        private Vector2[] uvs;
        private int[] triangles;
        private Mesh mesh;
        
        public MeshMaker()
        {
            terrainManager = TerrainManager.terrainManager;
            
            if (diffuseMap == null)
            {
                Debug.LogWarning("No material,Create diffuse!!");
                diffuseMap = new Material(Shader.Find("Diffuse"));
            }
            if (publicTexture == null)
            {
                publicTexture
                = Resources.Load<Texture>("Texture/atlas");
            }
        }
        public void setVertives(int cx, int cy, int cz, uniKey[] blockData, byte[] blockRData)
        {
            List<int> tri = new List<int>();
            List<Vector3> ver = new List<Vector3>();
            List<Vector2> uv = new List<Vector2>();

            for (int x = 0; x < terrainManager. chunkSize; x++)
            {
                for (int y = 0; y < terrainManager.chunkSize; y++)
                {
                    for (int z = 0; z < terrainManager.chunkSize; z++)
                    {
                        if (!blockData[terrainManager.getBlockIndex(x, y, z)].Equals(BlockAttacher.GetEmptyBlock()))
                        {
                            int blockIndex = terrainManager.getBlockIndex(x, y, z);
                            block currentBlock = BlockAttacher.blockAttacher.GetBlock(blockData[blockIndex]).GetBlockDrawer(blockRData[blockIndex]);//getBlockLoader(blockData[getBlockIndex(x, y, z)], blockRData[getBlockIndex(x, y, z)]);
                            currentBlock.addVerAndTri(ver, tri, uv, cx, cy, cz, x, y, z, terrainManager);

                        }
                    }
                }
            }
            vertives = ver.ToArray();
            triangles = tri.ToArray();
            uvs = uv.ToArray();
        }
        private void beforeDrawMesh(GameObject terrain)
        {
            if (terrain.GetComponent<MeshFilter>() == null)
            {
                terrain.AddComponent<MeshFilter>();
            }

            if (terrain.GetComponent<MeshRenderer>() == null)
            {
                terrain.AddComponent<MeshRenderer>();
            }
            terrain.GetComponent<Renderer>().material = diffuseMap;
            terrain.GetComponent<Renderer>().material.mainTexture = publicTexture;
            terrain.GetComponent<Renderer>().receiveShadows = false;
            mesh = terrain.GetComponent<MeshFilter>().mesh;//添加网格组件，并且添加到本地mesh变量里

        }
        public void drawMesh(GameObject terrain)
        {
            beforeDrawMesh(terrain);



            mesh.Clear();

            //给mesh 赋值
            mesh.vertices = vertives;//,pos);
            mesh.uv = uvs;
            mesh.triangles = triangles;
            //重置法线
            mesh.RecalculateNormals();
            //重置范围
            mesh.RecalculateBounds();
            if (terrain.GetComponent<MeshCollider>() == null)
            {
                terrain.AddComponent<MeshCollider>();
            }
            terrain.GetComponent<MeshCollider>().sharedMesh = mesh;
        }
    }
}
