using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class mouseOnGrid : MonoBehaviour, IPointerClickHandler,IPointerEnterHandler
{
    selectorController scon;
    public GameObject item;
    public Transform canvasTra;
    GUIMainController gmctrl;
    public void setUp(selectorController scon1)
    {
        scon=scon1;
    }
    public void setItem(GameObject item1)
    {
        this.item = item1;
        if (item != null) {
        item.transform.SetParent(gameObject.transform);
        item.transform.localPosition = Vector3.zero;
        }
    }
    public void setPicked(GameObject itemToPick)
    {
        if (canvasTra == null) canvasTra = gmctrl.gameObject.transform.parent;
        gmctrl.pickedItem = itemToPick;
        if (gmctrl.pickedItem!= null)
        {
            gmctrl.pickedItem.transform.SetParent(canvasTra);
            //bc.pickedItem.transform.localPosition = Vector3.zero;
        }
    }
    // Use this for initialization
    void Start()
    {
        gmctrl=GUIMainController.gmctrl;
    }

    // Update is called once per frame
    void Update()
    {
    }
    public void OnPointerEnter(PointerEventData eventData){
        //
        //Debug.Log("鼠标悬停");
        scon.targpos=transform.position;
    }
    public void OnPointerClick(PointerEventData eventData)
    {

        Debug.Log(item);
        
        switchPick();


    }
    
    void switchPick()
    {
        GameObject cup;
        cup = item;
        setItem(gmctrl.pickedItem) ;

        setPicked(cup);
    }

}
