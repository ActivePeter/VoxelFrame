using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MiniTipManager : MonoBehaviour {
	Text Message;
	float LifeCount;
	public bool DestroyStarted;
    // Use this for initializations
    void Start()
    {
        Message = transform.GetChild(0).GetComponent<Text>();
        Message.text = name;
        LifeCount = 0;
		DestroyStarted=false;
    }

    // Update is called once per frame
    void Update()
    {
		if(GetComponent<RectTransform>().sizeDelta.x!=transform.GetChild(0).GetComponent<RectTransform>().sizeDelta.x+20){
			GetComponent<RectTransform>().sizeDelta=new Vector2(transform.GetChild(0).GetComponent<RectTransform>().sizeDelta.x+20,GetComponent<RectTransform>().sizeDelta.y);
		Debug.Log("");
		}
		LifeCount+=Time.deltaTime;
		if(LifeCount>10){
			DestroyStarted=true;
		}
        if (transform.position.x != GUIMainController.gmctrl.upCenter.transform.position.x)
        {
            this.transform.position = new Vector3(MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(transform.position.x, GUIMainController.gmctrl.upCenter.transform.position.x), transform.position.y, transform.position.z);

        }
		if(DestroyStarted){
			if (Mathf.Abs(transform.position.y - GUIMainController.gmctrl.upCenter.transform.position.y)>0.1){
				this.transform.position = new Vector3(transform.position.x,MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(transform.position.y, GUIMainController.gmctrl.upCenter.transform.position.y),  transform.position.z);
			
			}else{
				Destroy(gameObject);

			}
			
		}
    }
}
