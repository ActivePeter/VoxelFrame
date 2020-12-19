using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class trigger : MonoBehaviour {
    public ray ray;
    public List<Collider> colis;
    void Start(){
        ray.trig=this;
    }
    // Use this for initialization
    void OnTriggerStay(Collider c)
    {
        
        if (c.tag=="mover"||c.tag=="DugBlock")
        {
            ray.buildAble = false;
            ray.triggerStaying=true;
            colis.Add(c);
            //Debug.Log("ray.buildAble = false;");
        }
    }
    private void OnTriggerExit(Collider c)
    {
        if (c.tag == "mover"||c.tag=="DugBlock")
        {
            ray.buildAble = true;
            ray.triggerStaying=false;
            colis.Remove(c);

            //Debug.Log("ray.buildAble = true;");
        }
    }
}
	
