using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.UI;

public class GUIMainController : MonoBehaviour
{
    public GameObject bag,inventory,bagBG_ALL,selector,dock,rlpGUI,miniTipModel,canvas,upCenter,itemModel,pickedItem;
    public selectorController selecon;
    private DockController dockcon;
    public static GUIMainController gmctrl;
    
    GameObject miniTip;
    public enum Guis{
        bag=1,
        RightLongPressGUI=2,
        noGui=0
    }
    
    public Guis CurrentGui=0;
    [MenuItem("Tools/Delete", false, 1)]
    static void Delete()//使删除游戏对象能够撤回
    {
        GameObject[] go = Selection.gameObjects;
        foreach (GameObject g in go)
        {
            //GameObject.DestroyImmediate(g);
            Undo.DestroyObjectImmediate(g);
        }
    }
    
    void Awake(){
        gmctrl=this;
        dockcon=dock.GetComponent<DockController>();
        selecon=selector.GetComponent<selectorController>();
        
    }
    // Use this for initialization
    void Start()
    {
        
        
        inventory.SetActive(false);
        bag.SetActive(false);
        rlpGUI.SetActive(false);
        //bagBG_ALL.SetActive
        //inventory.SetActive(false);
        dockcon.SetDockPos(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (pickedItem != null) pickedItem.transform.position = Input.mousePosition;
        if (Input.GetKeyDown(KeyCode.E))
        {
            if(CurrentGui!=Guis.bag){
                CloseGUI(CurrentGui);
                CurrentGui=Guis.bag;
                OpenGUI(CurrentGui);
            }else{
                CloseGUI(CurrentGui);
                CurrentGui=Guis.noGui;
            }
            
        }else if(Input.GetKeyDown(KeyCode.Escape)){
            CloseGUI(CurrentGui);
            CurrentGui=Guis.noGui;
        }
    }
    public void CloseGUI(Guis gui1){
        if(gui1==Guis.bag){
            inventory.SetActive(false);
            bag.SetActive(false);
            dockcon.SetDockPos(false);
            selecon.SetPosWhenBagFirstOpened();
        }else if(gui1==Guis.RightLongPressGUI){
            rlpGUI.SetActive(false);
            dockcon.gameObject.SetActive(true);
        }
    }
    public void OpenGUI(Guis gui1){
        if(miniTip!=null){
            miniTip.GetComponent<MiniTipManager>().DestroyStarted=true;
        }
        if(gui1==Guis.bag){
            inventory.SetActive(true);
            bag.SetActive(true);
            dockcon.SetDockPos(true);
            selecon.SetPosWhenBagFirstOpened();
        }else if(gui1==Guis.RightLongPressGUI){
            rlpGUI.SetActive(true);
            rlpGUI.GetComponent<RightLongPressGUIController>().init();
            dockcon.gameObject.SetActive(false);
        }
    }
    public void StartMiniTip(string message){
        if(miniTip==null){
            miniTip = Instantiate(miniTipModel);
            miniTip.name = message;
            miniTip.transform.SetParent(canvas.transform);
            miniTip.GetComponent<RectTransform>().anchoredPosition=new Vector2(60,-30);
        }else if(miniTip.name!=message){
            miniTip.GetComponent<MiniTipManager>().DestroyStarted=true;
            miniTip = Instantiate(miniTipModel);
            miniTip.name = message;
            miniTip.transform.SetParent(canvas.transform);
            miniTip.GetComponent<RectTransform>().anchoredPosition=new Vector2(60,-30);
        }
        
    }
    public void PickUpItem(uniKey itemID,int count){
        if (pickedItem== null)
        {
            GameObject GUIitem1 = (GameObject)Instantiate(itemModel);//uiItem实例化
            GUIitem1.GetComponent<uiItem>().FirstSetInfo(itemID, count);
            Transform canvasTra = gameObject.transform.parent;
            pickedItem = GUIitem1;
            pickedItem.transform.SetParent(canvasTra);
            //bc.pickedItem.transform.localPosition = Vector3.zero;
        }else{
            pickedItem.GetComponent<uiItem>().AddCount(count);
        }
        
        
        
    }
}
