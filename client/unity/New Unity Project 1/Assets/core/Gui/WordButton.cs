using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class WordButton : MonoBehaviour, IPointerClickHandler, IPointerEnterHandler, IPointerExitHandler
{
    public delegate void DoWhenClick();
    DoWhenClick dwc;
    // Use this for initialization
    void Start()
    {

    }
    public void SetUpButton(DoWhenClick dwc1)
    {
        dwc = dwc1;
    }
    public void OnPointerEnter(PointerEventData eventData)
    {
        GetComponent<Text>().color = MyTools.GetColor(0, 137, 251, 255);
    }
    public void OnPointerClick(PointerEventData eventData)
    {
        if (dwc != null) dwc();

    }
    public void OnPointerExit(PointerEventData eventData)
    {
        GetComponent<Text>().color = MyTools.GetColor(152, 152, 152, 255);
    }
    // Update is called once per frame
    void Update()
    {

    }
}
