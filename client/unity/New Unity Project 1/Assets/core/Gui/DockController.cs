using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DockController : MonoBehaviour {
    private GUIMainController maineCtrl;
    public GameObject gridModel,Main,dockSelector;
    public List<GameObject> gridInDock;
    private RectTransform dockRT;
    // Use this for initialization
    public ushort FindEmptyGrid()
    {
        for(ushort i = 0; i< gridInDock.Count; i++)
        {
            if (gridInDock[i].transform.childCount == 0) return i; 
        }
        return 1000;
    }
    void Start()
    {
        maineCtrl = Main.GetComponent<GUIMainController>();
        dockRT = gameObject.GetComponent<RectTransform>();
        BagController bc = maineCtrl.bag.GetComponent<BagController>();
        for (int i = 0; i < 10; i++)
        {
            GameObject go = (GameObject)Instantiate(gridModel);
            go.name = "gridInDock_" + i.ToString();
            //if(maineCtrl.selector==null) Debug.LogError("");
            go.GetComponent<mouseOnGrid>().setUp(maineCtrl.selector.GetComponent<selectorController>());
            go.transform.parent = transform;
            gridInDock.Add(go);
            //go.transform.localScale = Vector3.one;
        }
    }
    private void Update()
    {

    }
    public void SetDockPos(bool bagOpened1)
    {
        if (!bagOpened1)
        {
            if (dockRT == null)
            {
                dockRT = gameObject.GetComponent<RectTransform>();
            }
            this.dockRT.anchorMax = new Vector2(0.5f, 0);
            this.dockRT.anchorMin = new Vector2(0.5f, 0);
            this.dockRT.anchoredPosition = new Vector2(0, 29);

        }
        else
        {
            this.dockRT.anchorMax = new Vector2(0.5f, 0.5f);
                this.dockRT.anchorMin = new Vector2(0.5f, 0.5f);
                this.dockRT.anchoredPosition = new Vector2(0, -142.4f);;
            
        }
    }
}
