using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class rlpPutToBagPart : MonoBehaviour , IPointerClickHandler,IPointerEnterHandler,IPointerExitHandler{
	public delegate void DoWhenClick();
	DoWhenClick dwc;
	// Use this for initialization
	public void SetUpButton(DoWhenClick dwc1){
		dwc=dwc1;
	}
	public void OnPointerEnter(PointerEventData eventData){
		mouseIn=true;
    }
    public void OnPointerClick(PointerEventData eventData)
    {
		if(dwc!=null) dwc();
		
    }
	public void OnPointerExit(PointerEventData eventData)
    {
		mouseIn=false;
    }
	bool mouseIn;
	// Use this for initialization
	public bool Opened;
	RectTransform rt;
	void Start(){
		rt=GetComponent<RectTransform>();
	}
	void Update(){
		if(Opened){
			if(mouseIn)
            {
                if (!MyTools.floatCursoryEqual(rt.anchoredPosition.y,-89f))
                {
                    rt.anchoredPosition = new Vector2(rt.anchoredPosition.x, MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(rt.anchoredPosition.y, -89f));
                }

            }
            else
            {
                if (!MyTools.floatCursoryEqual(rt.anchoredPosition.y,-91.5f))
                {
                    rt.anchoredPosition = new Vector2(rt.anchoredPosition.x, MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(rt.anchoredPosition.y, -91.5f));
                }
			}
			
		}else{
			if(Mathf.Abs(rt.anchoredPosition.y+145f)>0.1f ){
				rt.anchoredPosition=new Vector2(rt.anchoredPosition.x,MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(rt.anchoredPosition.y,-145f));
			
			}else{
				gameObject.SetActive(false);
			}
			
		}
	}
	public void QuickClose(){
		if(rt!=null) rt.anchoredPosition=new Vector2(rt.anchoredPosition.x,-154);
		gameObject.SetActive(false);
		Opened=false;
	}
}
