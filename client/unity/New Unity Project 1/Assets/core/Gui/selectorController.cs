using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class selectorController : MonoBehaviour {
    public Vector3 targpos;
	public GameObject tContainer,Dock,selector,guiMain;
    public DockController dockController;
    BagController bgctrl;
    GUIMainController gmctrl;
	Text t;
	byte SelectedMode;//0 chooseBlock ，1 chooseDirection
	public byte indexOfChosen;
    public byte indexOfDirection;
	// Use this for initialization
	void Start () {
        gmctrl=guiMain.GetComponent<GUIMainController>();
		t=tContainer.GetComponent<Text>();
		dockController=Dock.GetComponent<DockController>();
        bgctrl=gmctrl.bag.GetComponent<BagController>();
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown(KeyCode.C))
        {
			if(SelectedMode<1){
				SelectedMode++;
			}else{
				SelectedMode=0;
			}
        }
        switch (SelectedMode)
        {
            case 0:
                t.text = "滚轮选择方块种类，按c切换选择方向";
                if (Input.GetAxis("Mouse ScrollWheel") < 0)
                {
                    if (indexOfChosen < dockController.gridInDock.Count-1)//The index is dockMax-1
                    {
                        indexOfChosen++;
                    }
                }
                else if (Input.GetAxis("Mouse ScrollWheel") > 0)
                {
                    if (indexOfChosen > 0)
                    {
                        indexOfChosen--;
                    }
                }
                break;
            case 1:
                if (dockController.gridInDock[indexOfChosen].GetComponent<mouseOnGrid>().item != null)
                {
                    //获取itemID
                    uniKey itemIDSelected = dockController.gridInDock[indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID;
                    int directionsCount=ItemAttacher.itemAttacher.itemDic[itemIDSelected].getBlockDecription().GetDirectionsCount();
                    if(indexOfDirection > directionsCount - 1){
                        indexOfDirection=0;
                    }
                    if (Input.GetAxis("Mouse ScrollWheel") < 0)
                    {
                        if (indexOfDirection < directionsCount - 1)
                        {
                            indexOfDirection++;
                            rotateObjectIfExist();
                        }
                    }
                    else if (Input.GetAxis("Mouse ScrollWheel") > 0)
                    {
                        if (indexOfDirection > 0)
                        {
                            indexOfDirection--;
                            rotateObjectIfExist();
                        }
                    }
                    t.text = "滚轮选择方块方向，按c切换选择方块  当前序号：" + indexOfDirection;
                    
                
                }else{
                    t.text = "当前选择物品栏为空，无法选择方向，按c切换选择方块" ;
                }
                
                break;
        }

        SetPos();
        //Debug.LogError(targpos);
    }
    public void rotateObjectIfExist(){
        if (ray._ray.previewOfBlockInHand != null)
        {
            ItemAttacher.itemAttacher.itemDic[dockController.gridInDock[indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID].getBlockDecription().GetBlockDrawer(indexOfDirection).getBlockObjectRotate(ray._ray.previewOfBlockInHand);
        }
    }
    void SetPos(){
        //if(Dock==null) Debug.Log(1122221);
        //if(dockController==null) Debug.Log(111);
        //GameObject a=dockController.gridInDock[indexOfChosen];
        //this.gameObject.GetComponent<RectTransform>().anchoredPosition=dockController.gridInDock[indexOfChosen].GetComponent<RectTransform>().anchoredPosition;
        /*if(bgctrl.pickedItem!=null){
            selector.transform.position=bgctrl.pickedItem.transform.position;
        }else{*/
            if (gmctrl.CurrentGui==GUIMainController.Guis.noGui)
            {
                SetPosWhenBagFirstOpened();
                if (Vector3.Distance(selector.transform.position, targpos) < 0.1f)
                {
                    //Debug.Log("到达");
                    selector.transform.position = targpos;
                }
                else
                {
                    selector.transform.position = Vector3.Lerp(selector.transform.position, targpos, 0.3f);
                }
            }
            else if(gmctrl.CurrentGui==GUIMainController.Guis.bag)
            {

                if (Vector3.Distance(selector.transform.position, targpos) < 0.1f)
                {
                    //Debug.Log("到达");
                    selector.transform.position = targpos;
                }
                else
                {
                    selector.transform.position = Vector3.Lerp(selector.transform.position, targpos, 0.3f);
                }
                //Debug.LogError(targpos);
            }else{
                selector.transform.position = Vector3.Lerp(selector.transform.position, new Vector3(-100,-100,0), 0.3f);
            }
        //}

    }
    public void SetPosWhenBagFirstOpened()
    {
        targpos = dockController.gridInDock[indexOfChosen].transform.position;
    }
}
