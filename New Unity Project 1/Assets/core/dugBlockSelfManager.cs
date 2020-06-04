using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class dugBlockSelfManager : MonoBehaviour {
    private TerrainManager terraManager;
    GameObject picker;
    bool startedPicking,recoverActivated,recoverAdded,recoveringLoadAllowed;
    float timeInterval;
    private DateTime CreatedTime;
    dugBlockManager dm;
    Material diffuseMap;
    public uniKey blockID;

    Vector3 to;
    bool isTOloaded;
    // Use this for initialization
    void Start()
    {
        dm = dugBlockManager.dm;
        startedPicking = false;
        timeInterval = 0.05f;
        CreatedTime  = DateTime.Now;
        isTOloaded = false;
        recoverAdded = false;
        recoveringLoadAllowed = false;
	}
    public void startPicking(GameObject p)
    {
        
        picker = p;
        startedPicking = true;
        Debug.Log(startedPicking);
    }
    // Update is called once per frame
    void Update()
    {

        //Debug.Log(DateTime.Now.Ticks - CreatedTime.Ticks);
        if (startedPicking)
        {
            transform.position = Vector3.MoveTowards(transform.position, picker.transform.position + Vector3.up , 0.2f);
            transform.localScale = Vector3.MoveTowards(transform.localScale, Vector3.zero, 0.2f);
            if (Vector3.Distance(transform.position, picker.transform.position + Vector3.up) < 0.001)
            {
                Destroy(gameObject);
            }
        }
        else if (DateTime.Now.Ticks - CreatedTime.Ticks > timeInterval * 600000000)
        {
            if (!recoverAdded)
            {
                dm.AddRecover(this);
                recoverAdded = true;
            }
            if (recoveringLoadAllowed)
            {

                if (dm.recovering)
                {
                    to = new Vector3(Mathf.FloorToInt(transform.position.x) + 0.5f, Mathf.FloorToInt(transform.position.y) + 0.5f, Mathf.FloorToInt(transform.position.z) + 0.5f);
                    if (ray.trig != null)
                    {

                        if (ray.trig.colis.Contains(GetComponent<Collider>()))
                        {
                            ray.trig.ray.buildAble = true;
                            ray.trig.ray.triggerStaying=false;
                        }
                    }
                    
                    Destroy(gameObject.GetComponent<Rigidbody>());
                    transform.position = to;
                    //transform.position = Vector3.MoveTowards(transform.position, to, 0.2f);
                    transform.localScale = Vector3.MoveTowards(transform.localScale, Vector3.one, 0.1f);
                    
                    transform.rotation=MyTools.RotateInUpdateWithFixedTime(transform.rotation,0,0,0);
                    //Debug.Log(to);
                    //transform.forward = Vector3.RotateTowards(transform.forward, Vector3.forward, 0.05f, 0f);
                    if (dm.recovering)
                    {
                        if (Vector3.Distance(transform.position, to) < 0.001 && Vector3.Distance(transform.localScale, Vector3.one) < 0.0001 && Vector3.Distance(transform.forward, Vector3.forward) < 0.5)
                        {

                            //Debug.Log(Mathf.RoundToInt(to.x) + " " + Mathf.RoundToInt(to.y) + " " + Mathf.RoundToInt(to.z));
                            terraManager.BuildBlockInEmpty(Mathf.FloorToInt(to.x), Mathf.FloorToInt(to.y), Mathf.FloorToInt(to.z), blockID, 0);
                            //terraManager.BuildBlock(Mathf.FloorToInt(to.x), Mathf.FloorToInt(to.y), Mathf.FloorToInt(to.z), BlockAttacher.GetEmptyBlock(), 80);
                            //ray._ray.Build(to);
                            Destroy(gameObject);
                            dm.recovering = false;
                        }
                    }
                }
            }
        }
    }
    public void startRecover()
    {
        recoveringLoadAllowed = true;
    }
    public void Init(uniKey blockID1){
        blockID=blockID1;
        terraManager=TerrainManager.terrainManager;
    }
}
