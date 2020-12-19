using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class BagController : MonoBehaviour{

    public GameObject itemModel, gridModel;
    public GameObject Dock,guiMain; // 当前拾取的物品
    public static BagController bagController;
    IconManager iconManager;
    private DockController dock;
    GUIMainController gmctrl;
    public List<GameObject> gridInBag;//界面中的格子
    // Use this for initialization
    void Start () {
        bagController=this;
        dock = Dock.GetComponent<DockController>();
        gmctrl=guiMain.GetComponent<GUIMainController>();
        iconManager=IconManager.iconManager;
        for (int i = 0; i < 30; i++)
        {
            GameObject go = (GameObject)Instantiate(gridModel);
            go.name = "gridInBag_"+i.ToString();
            go.GetComponent<mouseOnGrid>().setUp(gmctrl.selector.GetComponent<selectorController>());
            go.transform.parent = transform;
            gridInBag.Add(go);
            //go.transform.localScale = Vector3.one;
        }
        //addItemToGrid(1,0);
        //addItemToGrid(1, 1);
    }
    
    // Update is called once per frame
    public ushort FindEmptyGrid()
    {
        for (ushort i = 0; i < gridInBag.Count; i++)
        {
            if (gridInBag[i].transform.childCount == 0) return i;
        }
        return 1000;
    }
    private ushort FindGridCanBeFilled(int itemID1)
    {
        for (ushort i = 0; i < gridInBag.Count; i++)
        {
            if (!gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().ifIsFullSet()) {
                return i;
            }else if(gridInBag[i].transform.childCount == 0){
                return i;
            }
        }
        return 1000;
    }
    

    public bool addItemToGridAll(uniKey itemID,int count)//返回给picker 确认添加成功后开始销毁
    {
        for (ushort i = 0; i < dock.gridInDock.Count; i++){
            if(dock.gridInDock[i].GetComponent<mouseOnGrid>().item!=null&&dock.gridInDock[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID.Equals(itemID))
            {
                //Debug.Log("fullset"+gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().ifIsFullSet());
                if (!dock.gridInDock[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().ifIsFullSet())
                {
                    Debug.Log("COUNT1:"+count);
                    count = dock.gridInDock[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().AddCountAndReturnSurplus(count);
                    Debug.Log("COUNT2:"+count);
                    if (count == 0)
                    {
                        return true;
                    }
                }
            }
            else if(dock.gridInDock[i].transform.childCount == 0){
                GameObject GUIitem1 = (GameObject)Instantiate(itemModel);//uiItem实例化
                
                GUIitem1.GetComponent<uiItem>().FirstSetInfo(itemID,1);
                dock.gridInDock[i].GetComponent<mouseOnGrid>().setItem(GUIitem1);
                Debug.Log("COUNT3:"+count);
                count = dock.gridInDock[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().AddCountAndReturnSurplus(count-1);
                Debug.Log("COUNT4:"+count);
                if (count == 0)
                {
                    return true;
                }
            }
        }
        for (ushort i = 0; i < gridInBag.Count; i++)
        {
            //if(gridInBag[i].GetComponent<mouseOnGrid>().item==null)ridInBag[i].GetComponent<mouseOnGrid>().item==nul");
            if(gridInBag[i].GetComponent<mouseOnGrid>().item!=null&&gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID.Equals(itemID))
            {
                //Debug.Log("fullset"+gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().ifIsFullSet());
                if (!gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().ifIsFullSet())
                {
                    count = gridInBag[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().AddCountAndReturnSurplus(count);
                    
                    if (count == 0)
                    {
                        return true;
                    }
                }
            }
            else if(gridInBag[i].transform.childCount == 0){
                GameObject GUIitem1 = (GameObject)Instantiate(itemModel);//uiItem实例化
                GUIitem1.GetComponent<uiItem>().FirstSetInfo(itemID,1);
                gridInBag[i].GetComponent<mouseOnGrid>().setItem(GUIitem1);
                count = dock.gridInDock[i].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().AddCountAndReturnSurplus(count-1);

                if (count == 0)
                {
                    return true;
                }
            }
        }
        return false;
        //配置uiitem所含内容
        /*int a = dock.FindEmptyGrid();
        if (a<1000)
        {
            GameObject item1 = (GameObject)Instantiate(itemModel);//uiItem实例化
            item1.GetComponent<uiItem>().FirstSetInfo(itemDic[itemID]);
            dock.gridInDock[a].GetComponent<mouseOnGrid>().setItem(item1);
            return true;
        }
        else
        {
            
            int b = FindEmptyGrid();Debug.Log(b);
            if (b < 1000)
            {
                if(gridInBag[b].GetComponent<mouseOnGrid>().item!=null){

                }else{

                }
                GameObject item1 = (GameObject)Instantiate(itemModel);//uiItem实例化
                item1.GetComponent<uiItem>().FirstSetInfo(itemDic[itemID]);
                gridInBag[b].GetComponent<mouseOnGrid>().setItem(item1);
                return true;
            }
        }
        return false;*/
    }

    // 背包核心逻辑：交换




}
/*public GameObject itemModel, gridModel;
public GameObject pickedItem; // 当前拾取的物品

public List<GameObject> grids;//界面中的格子
public List<item> items;//物品id和对象
                        // Use this for initialization
void Start()
{
    items = new List<item>();
    items.Add(new item(1));
    for (int i = 0; i < 64; i++)
    {
        GameObject go = (GameObject)Instantiate(gridModel);

        go.transform.parent = transform;
        grids.Add(go);
        //go.transform.localScale = Vector3.one;
    }
    addItemToGrid(1, 0);
}

// Update is called once per frame
void Update()
{

}
private void addItemToGrid(int itemID, int gridId)
{
    GameObject UIitem1 = (GameObject)Instantiate(itemModel);
    UIitem1.GetComponent<uiItem>().setInfo(items[0]);
    UIitem1.transform.parent = (grids[gridID].transform);
    Debug.Log("");
}
public int gridID;*/