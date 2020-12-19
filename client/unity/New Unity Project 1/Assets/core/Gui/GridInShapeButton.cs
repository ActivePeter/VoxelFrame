using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class GridInShapeButton : MonoBehaviour , IPointerClickHandler{
	public delegate void DoWhenClick();
	public int ShapeID;
	DoWhenClick dwc;
	// Use this for initialization
	void Start () {
		
	}
	public void SetUpButton(DoWhenClick dwc1,int ShapeID1){
		ShapeID=ShapeID1;
		dwc=dwc1;
	}
    public void OnPointerClick(PointerEventData eventData)
    {
		if(dwc!=null) dwc();
		
    }
	// Update is called once per frame
	void Update () {
		
	}
}
