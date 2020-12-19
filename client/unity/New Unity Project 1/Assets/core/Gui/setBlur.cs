using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class setBlur : MonoBehaviour {
    Camera cblur;
    public GameObject mc,main;
    GUIMainController gmctrl;
    
    // Use this for initialization
    void Start () {
        cblur = GameObject.Find("mcblur").GetComponent<Camera>();
        gmctrl=main.GetComponent<GUIMainController>();
    }
	
	// Update is called once per frame
	void Update () {
        setBlurSize();
        if(gmctrl.CurrentGui!=GUIMainController.Guis.noGui){
            GetComponent<Image>().enabled=true;
        }else{

            GetComponent<Image>().enabled=false;
        }
    }
    void setBlurSize()
    {
        Vector2 rect= GetComponent<RectTransform>().sizeDelta;
        rect.x = rect.y =Screen.width;
         
        GetComponent<RectTransform>().sizeDelta=rect;
        float w = Mathf.Atan(Screen.width * Mathf.Tan(mc.GetComponent<Camera>().fieldOfView / 360 * Mathf.PI) / Screen.height);
        cblur.fieldOfView = 2 * w / Mathf.PI * 180;
    }
}
