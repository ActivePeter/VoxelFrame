using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RightLongPressGUIController : MonoBehaviour {
    enum GUIs
    {
        Info = 1,
        Shape = 2

    }
    GUIMainController gmctrl;
    selectorController selecon;
    uniKey itemid;
    GUIs CurrentGUI;
    // Use this for initialization
    void Start()
    {
        gmctrl = GUIMainController.gmctrl;
        selecon = gmctrl.selecon;
        
        CurrentGUI = GUIs.Info;
    }

    // Update is called once per frame
    void Update()
    {

    }
    public List<GameObject> gridsInShapeGUI;
    public GameObject gridModel;
    int itemsCount;
    void setItemCount(int count){
        itemsCount=count;
        transform.GetChild(0). GetChild(8).GetComponent<Text>().text=count.ToString();
    }
    void SetRlpPutToBagPartOpened(bool Opened){
        if(Opened){
            transform.GetChild(0).GetChild(9).gameObject.GetComponent<rlpPutToBagPart>().Opened = true;
            if (!transform.GetChild(0).GetChild(9).gameObject.active)
            {
                transform.GetChild(0).GetChild(9).gameObject.SetActive(true);
            }
        }else{
            transform.GetChild(0).GetChild(9).GetComponent<rlpPutToBagPart>().Opened=false;
        }
    }
    public void init()
    {
        //fix time delay
        if(gmctrl==null) {
            gmctrl = GUIMainController.gmctrl;
            selecon = gmctrl.selecon;

            CurrentGUI = GUIs.Info;
        }

        transform.GetChild(0).GetChild(9).GetComponent<rlpPutToBagPart>().QuickClose();
        transform.GetChild(0).GetChild(9).GetComponent<rlpPutToBagPart>().SetUpButton(delegate(){
            if(gmctrl.pickedItem!=null){
                BagController.bagController.addItemToGridAll(gmctrl.pickedItem.GetComponent<uiItem>().itemID, gmctrl.pickedItem.GetComponent<uiItem>().itemsCount);
                Destroy(gmctrl.pickedItem);
            }
            
            SetRlpPutToBagPartOpened(false);
        });

        uiItem CurrentItem=selecon.dockController.gridInDock[selecon.indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>();
        setItemCount(CurrentItem.itemsCount) ;
        itemid = CurrentItem.itemID;
		BlockDescription block=ItemAttacher.itemAttacher.itemDic[itemid].getBlockDecription();
        transform.GetChild(0).GetChild(4).GetComponent<RawImage>().texture = block.GetIcon();//gmctrl.iconManager.getItemIcon(itemid);
        for (int i = 0; i < transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetChild(0).childCount; i++)
        {
            Destroy(transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetChild(0).GetChild(i).gameObject);

        }
		Shapes[] ShapeArr=block.GetShapeArr();
		Debug.Log(itemid);
		foreach(Shapes shape in ShapeArr){
			if(block.GetShape().shape!=shape){
                GameObject go = (GameObject)Instantiate(gridModel);
                go.name = "gridInShapeGUI_" + shape.ToString();
                //Debug.Log((int)ShapeArr[i + 1]);
                go.GetComponent<RawImage>().texture = BlockAttacher.blockAttacher.GetBlock(block.GetBlockID(),shape).GetIcon();
                go.transform.SetParent(transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetChild(0));
                int[] SwitchCount=BlockShapeAttacher.blockShapeAttacher.getSwitchCount(block.GetShape().value,BlockShapeAttacher.blockShapeAttacher.GetBlockShape(shape).value);
                go.GetComponent<GridInShapeButton>().SetUpButton(delegate (){
                    if(CurrentItem.itemsCount>=SwitchCount[0]){
                        SetRlpPutToBagPartOpened(true);
                        gmctrl.PickUpItem(MyTools.Unikey(itemid.id1, (int)shape), SwitchCount[1]);
                        CurrentItem.MinusCountAndReturnSurplus(SwitchCount[0]);
                        setItemCount(itemsCount-SwitchCount[0]);
                    }else{
                        gmctrl.StartMiniTip("当前选中方块组已经不够合成此物体");
                    }
					if(gmctrl.pickedItem!=null){

                    }
				}, (int)shape);
                gridsInShapeGUI.Add(go);
			}
		}
        /*for (int i = 0; i < BlockAttacher.GetShapeCount(itemid); i++)
        {
			
           
            //go.transform.localScale = Vector3.one;
        }*/
        transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetChild(0).GetComponent<RectTransform>().sizeDelta = new Vector2(45 * 2, transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetChild(0).GetComponent<RectTransform>().sizeDelta.y);
        transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetComponent<RectTransform>().sizeDelta = new Vector2(45 * 2 + 16, transform.GetChild(0).GetChild(6).GetChild(0).GetChild(0).GetChild(0).GetComponent<RectTransform>().sizeDelta.y);
        transform.GetChild(0).GetChild(5).gameObject.SetActive(true);
        transform.GetChild(0).GetChild(6).gameObject.SetActive(false);
        transform.GetChild(0).GetChild(7).GetComponent<Text>().text = "切换到加工面板";
        CurrentGUI = GUIs.Info;
        transform.GetChild(0).GetChild(7).GetComponent<WordButton>().SetUpButton(delegate ()
        {
            if (CurrentGUI == GUIs.Info)
            {
                transform.GetChild(0).GetChild(5).gameObject.SetActive(false);
                transform.GetChild(0).GetChild(6).gameObject.SetActive(true);
                transform.GetChild(0).GetChild(7).GetComponent<Text>().text = "切换到信息面板";
                CurrentGUI = GUIs.Shape;
            }
            else if (CurrentGUI == GUIs.Shape)
            {
                transform.GetChild(0).GetChild(5).gameObject.SetActive(true);
                transform.GetChild(0).GetChild(6).gameObject.SetActive(false);
                transform.GetChild(0).GetChild(7).GetComponent<Text>().text = "切换到加工面板";
                CurrentGUI = GUIs.Info;
            }

        });
	} 
}
