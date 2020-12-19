using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Picker : MonoBehaviour {
    public GameObject bag;
    BagController bc;
	// Use this for initialization
	void Start () {
        bc = bag.GetComponent<BagController>();
        
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnTriggerEnter(Collider c)
    {
        Debug.Log(c.tag);
        if (c.tag == "DugBlock")
        {
            if (bc.addItemToGridAll(c.GetComponent<dugBlockSelfManager>().blockID,1))
            {
                if (ray.trig != null)
                {
                    if (ray.trig.colis.Contains(c))
                    {
                        Debug.Log("buildAble = true;picker");
                        ray.trig.ray.buildAble = true;
                        ray.trig.ray.triggerStaying=false;
                    }
                }
                Destroy(c.GetComponent<Rigidbody>());
                c.GetComponent<MeshCollider>().enabled = false;
                c.GetComponent<dugBlockSelfManager>().startPicking(this.gameObject);
            }
        }
    }
}
